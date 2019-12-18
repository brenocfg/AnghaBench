#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct input_absinfo {int maximum; float minimum; } ;
struct TYPE_6__ {int* absMap; int** hats; struct input_absinfo* absInfo; } ;
struct TYPE_7__ {TYPE_1__ linjs; } ;
typedef  TYPE_2__ _GLFWjoystick ;

/* Variables and functions */
 int ABS_HAT0X ; 
 int ABS_HAT3Y ; 
#define  GLFW_HAT_CENTERED 136 
#define  GLFW_HAT_DOWN 135 
#define  GLFW_HAT_LEFT 134 
#define  GLFW_HAT_LEFT_DOWN 133 
#define  GLFW_HAT_LEFT_UP 132 
#define  GLFW_HAT_RIGHT 131 
#define  GLFW_HAT_RIGHT_DOWN 130 
#define  GLFW_HAT_RIGHT_UP 129 
#define  GLFW_HAT_UP 128 
 int /*<<< orphan*/  _glfwInputJoystickAxis (TYPE_2__*,int const,float) ; 
 int /*<<< orphan*/  _glfwInputJoystickHat (TYPE_2__*,int const,char const) ; 

__attribute__((used)) static void handleAbsEvent(_GLFWjoystick* js, int code, int value)
{
    const int index = js->linjs.absMap[code];

    if (code >= ABS_HAT0X && code <= ABS_HAT3Y)
    {
        static const char stateMap[3][3] =
        {
            { GLFW_HAT_CENTERED, GLFW_HAT_UP,       GLFW_HAT_DOWN },
            { GLFW_HAT_LEFT,     GLFW_HAT_LEFT_UP,  GLFW_HAT_LEFT_DOWN },
            { GLFW_HAT_RIGHT,    GLFW_HAT_RIGHT_UP, GLFW_HAT_RIGHT_DOWN },
        };

        const int hat = (code - ABS_HAT0X) / 2;
        const int axis = (code - ABS_HAT0X) % 2;
        int* state = js->linjs.hats[hat];

        // NOTE: Looking at several input drivers, it seems all hat events use
        //       -1 for left / up, 0 for centered and 1 for right / down
        if (value == 0)
            state[axis] = 0;
        else if (value < 0)
            state[axis] = 1;
        else if (value > 0)
            state[axis] = 2;

        _glfwInputJoystickHat(js, index, stateMap[state[0]][state[1]]);
    }
    else
    {
        const struct input_absinfo* info = &js->linjs.absInfo[code];
        float normalized = value;

        const int range = info->maximum - info->minimum;
        if (range)
        {
            // Normalize to 0.0 -> 1.0
            normalized = (normalized - info->minimum) / range;
            // Normalize to -1.0 -> 1.0
            normalized = normalized * 2.0f - 1.0f;
        }

        _glfwInputJoystickAxis(js, index, normalized);
    }
}