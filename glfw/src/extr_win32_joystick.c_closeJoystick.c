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
struct TYPE_6__ {int /*<<< orphan*/  objects; scalar_t__ device; } ;
struct TYPE_7__ {TYPE_1__ win32; } ;
typedef  TYPE_2__ _GLFWjoystick ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_DISCONNECTED ; 
 int /*<<< orphan*/  IDirectInputDevice8_Release (scalar_t__) ; 
 int /*<<< orphan*/  IDirectInputDevice8_Unacquire (scalar_t__) ; 
 int /*<<< orphan*/  _glfwFreeJoystick (TYPE_2__*) ; 
 int /*<<< orphan*/  _glfwInputJoystick (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void closeJoystick(_GLFWjoystick* js)
{
    if (js->win32.device)
    {
        IDirectInputDevice8_Unacquire(js->win32.device);
        IDirectInputDevice8_Release(js->win32.device);
    }

    free(js->win32.objects);

    _glfwFreeJoystick(js);
    _glfwInputJoystick(js, GLFW_DISCONNECTED);
}