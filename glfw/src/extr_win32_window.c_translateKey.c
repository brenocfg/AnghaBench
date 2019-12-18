#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WPARAM ;
struct TYPE_5__ {int* keycodes; } ;
struct TYPE_7__ {TYPE_1__ win32; } ;
struct TYPE_6__ {scalar_t__ message; scalar_t__ wParam; scalar_t__ time; int /*<<< orphan*/  lParam; } ;
typedef  TYPE_2__ MSG ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int GLFW_KEY_LEFT_CONTROL ; 
 int GLFW_KEY_RIGHT_CONTROL ; 
 scalar_t__ GetMessageTime () ; 
 int HIWORD (int /*<<< orphan*/ ) ; 
 int KF_EXTENDED ; 
 int /*<<< orphan*/  PM_NOREMOVE ; 
 scalar_t__ PeekMessageW (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VK_CONTROL ; 
 scalar_t__ VK_MENU ; 
 scalar_t__ VK_PROCESSKEY ; 
 scalar_t__ WM_KEYDOWN ; 
 scalar_t__ WM_KEYUP ; 
 scalar_t__ WM_SYSKEYDOWN ; 
 scalar_t__ WM_SYSKEYUP ; 
 int _GLFW_KEY_INVALID ; 
 TYPE_3__ _glfw ; 

__attribute__((used)) static int translateKey(WPARAM wParam, LPARAM lParam)
{
    // The Ctrl keys require special handling
    if (wParam == VK_CONTROL)
    {
        MSG next;
        DWORD time;

        // Right side keys have the extended key bit set
        if (HIWORD(lParam) & KF_EXTENDED)
            return GLFW_KEY_RIGHT_CONTROL;

        // HACK: Alt Gr sends Left Ctrl and then Right Alt in close sequence
        //       We only want the Right Alt message, so if the next message is
        //       Right Alt we ignore this (synthetic) Left Ctrl message
        time = GetMessageTime();

        if (PeekMessageW(&next, NULL, 0, 0, PM_NOREMOVE))
        {
            if (next.message == WM_KEYDOWN ||
                next.message == WM_SYSKEYDOWN ||
                next.message == WM_KEYUP ||
                next.message == WM_SYSKEYUP)
            {
                if (next.wParam == VK_MENU &&
                    (HIWORD(next.lParam) & KF_EXTENDED) &&
                    next.time == time)
                {
                    // Next message is Right Alt down so discard this
                    return _GLFW_KEY_INVALID;
                }
            }
        }

        return GLFW_KEY_LEFT_CONTROL;
    }

    if (wParam == VK_PROCESSKEY)
    {
        // IME notifies that keys have been filtered by setting the virtual
        // key-code to VK_PROCESSKEY
        return _GLFW_KEY_INVALID;
    }

    return _glfw.win32.keycodes[HIWORD(lParam) & 0x1FF];
}