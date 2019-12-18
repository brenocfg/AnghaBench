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
typedef  int /*<<< orphan*/  _GLFWjoystick ;
struct TYPE_3__ {int /*<<< orphan*/  (* joystick ) (int const,int) ;} ;
struct TYPE_4__ {int joysticks; TYPE_1__ callbacks; } ;

/* Variables and functions */
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  stub1 (int const,int) ; 

void _glfwInputJoystick(_GLFWjoystick* js, int event)
{
    const int jid = (int) (js - _glfw.joysticks);

    if (_glfw.callbacks.joystick)
        _glfw.callbacks.joystick(jid, event);
}