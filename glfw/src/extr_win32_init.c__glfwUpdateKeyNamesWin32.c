#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  chars ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int* scancodes; int /*<<< orphan*/ * keynames; } ;
struct TYPE_4__ {TYPE_1__ win32; } ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int GLFW_KEY_KP_0 ; 
 int GLFW_KEY_KP_ADD ; 
 int GLFW_KEY_LAST ; 
 int GLFW_KEY_SPACE ; 
 int /*<<< orphan*/  MAPVK_VSC_TO_VK ; 
 int /*<<< orphan*/  MapVirtualKey (int,int /*<<< orphan*/ ) ; 
 int ToUnicode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const VK_ADD ; 
 int /*<<< orphan*/  const VK_DECIMAL ; 
 int /*<<< orphan*/  const VK_DIVIDE ; 
 int /*<<< orphan*/  const VK_MULTIPLY ; 
 int /*<<< orphan*/  const VK_NUMPAD0 ; 
 int /*<<< orphan*/  const VK_NUMPAD1 ; 
 int /*<<< orphan*/  const VK_NUMPAD2 ; 
 int /*<<< orphan*/  const VK_NUMPAD3 ; 
 int /*<<< orphan*/  const VK_NUMPAD4 ; 
 int /*<<< orphan*/  const VK_NUMPAD5 ; 
 int /*<<< orphan*/  const VK_NUMPAD6 ; 
 int /*<<< orphan*/  const VK_NUMPAD7 ; 
 int /*<<< orphan*/  const VK_NUMPAD8 ; 
 int /*<<< orphan*/  const VK_NUMPAD9 ; 
 int /*<<< orphan*/  const VK_SUBTRACT ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void _glfwUpdateKeyNamesWin32(void)
{
    int key;
    BYTE state[256] = {0};

    memset(_glfw.win32.keynames, 0, sizeof(_glfw.win32.keynames));

    for (key = GLFW_KEY_SPACE;  key <= GLFW_KEY_LAST;  key++)
    {
        UINT vk;
        int scancode, length;
        WCHAR chars[16];

        scancode = _glfw.win32.scancodes[key];
        if (scancode == -1)
            continue;

        if (key >= GLFW_KEY_KP_0 && key <= GLFW_KEY_KP_ADD)
        {
            const UINT vks[] = {
                VK_NUMPAD0,  VK_NUMPAD1,  VK_NUMPAD2, VK_NUMPAD3,
                VK_NUMPAD4,  VK_NUMPAD5,  VK_NUMPAD6, VK_NUMPAD7,
                VK_NUMPAD8,  VK_NUMPAD9,  VK_DECIMAL, VK_DIVIDE,
                VK_MULTIPLY, VK_SUBTRACT, VK_ADD
            };

            vk = vks[key - GLFW_KEY_KP_0];
        }
        else
            vk = MapVirtualKey(scancode, MAPVK_VSC_TO_VK);

        length = ToUnicode(vk, scancode, state,
                           chars, sizeof(chars) / sizeof(WCHAR),
                           0);

        if (length == -1)
        {
            length = ToUnicode(vk, scancode, state,
                               chars, sizeof(chars) / sizeof(WCHAR),
                               0);
        }

        if (length < 1)
            continue;

        WideCharToMultiByte(CP_UTF8, 0, chars, 1,
                            _glfw.win32.keynames[key],
                            sizeof(_glfw.win32.keynames[key]),
                            NULL, NULL);
    }
}