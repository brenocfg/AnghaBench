#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  name; int /*<<< orphan*/  guid; scalar_t__ axes; scalar_t__ buttons; } ;
typedef  TYPE_1__ _GLFWmapping ;
struct TYPE_8__ {int /*<<< orphan*/  guid; } ;
typedef  TYPE_2__ _GLFWjoystick ;

/* Variables and functions */
 int GLFW_GAMEPAD_AXIS_LAST ; 
 int GLFW_GAMEPAD_BUTTON_LAST ; 
 int /*<<< orphan*/  GLFW_INVALID_VALUE ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* findMapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isValidElementForJoystick (scalar_t__,TYPE_2__ const*) ; 

__attribute__((used)) static _GLFWmapping* findValidMapping(const _GLFWjoystick* js)
{
    _GLFWmapping* mapping = findMapping(js->guid);
    if (mapping)
    {
        int i;

        for (i = 0;  i <= GLFW_GAMEPAD_BUTTON_LAST;  i++)
        {
            if (!isValidElementForJoystick(mapping->buttons + i, js))
            {
                _glfwInputError(GLFW_INVALID_VALUE,
                                "Invalid button in gamepad mapping %s (%s)",
                                mapping->guid,
                                mapping->name);
                return NULL;
            }
        }

        for (i = 0;  i <= GLFW_GAMEPAD_AXIS_LAST;  i++)
        {
            if (!isValidElementForJoystick(mapping->axes + i, js))
            {
                _glfwInputError(GLFW_INVALID_VALUE,
                                "Invalid axis in gamepad mapping %s (%s)",
                                mapping->guid,
                                mapping->name);
                return NULL;
            }
        }
    }

    return mapping;
}