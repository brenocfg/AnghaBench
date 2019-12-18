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
struct TYPE_3__ {char* clipboardString; int clipboardSize; } ;
struct TYPE_4__ {TYPE_1__ wl; } ;
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 char* realloc (char*,int) ; 

__attribute__((used)) static GLFWbool growClipboardString(void)
{
    char* clipboard = _glfw.wl.clipboardString;

    clipboard = realloc(clipboard, _glfw.wl.clipboardSize * 2);
    if (!clipboard)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Wayland: Impossible to grow clipboard string");
        return GLFW_FALSE;
    }
    _glfw.wl.clipboardString = clipboard;
    _glfw.wl.clipboardSize = _glfw.wl.clipboardSize * 2;
    return GLFW_TRUE;
}