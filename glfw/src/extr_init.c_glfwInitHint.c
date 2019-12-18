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
struct TYPE_3__ {int chdir; int menubar; } ;
struct TYPE_4__ {int hatButtons; TYPE_1__ ns; } ;

/* Variables and functions */
#define  GLFW_COCOA_CHDIR_RESOURCES 130 
#define  GLFW_COCOA_MENUBAR 129 
 int /*<<< orphan*/  GLFW_INVALID_ENUM ; 
#define  GLFW_JOYSTICK_HAT_BUTTONS 128 
 TYPE_2__ _glfwInitHints ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,int) ; 

void glfwInitHint(int hint, int value)
{
    switch (hint)
    {
        case GLFW_JOYSTICK_HAT_BUTTONS:
            _glfwInitHints.hatButtons = value;
            return;
        case GLFW_COCOA_CHDIR_RESOURCES:
            _glfwInitHints.ns.chdir = value;
            return;
        case GLFW_COCOA_MENUBAR:
            _glfwInitHints.ns.menubar = value;
            return;
    }

    _glfwInputError(GLFW_INVALID_ENUM,
                    "Invalid init hint 0x%08X", hint);
}