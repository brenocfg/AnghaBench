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
struct TYPE_6__ {int /*<<< orphan*/  fd; } ;
struct TYPE_7__ {TYPE_1__ linjs; } ;
typedef  TYPE_2__ _GLFWjoystick ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_DISCONNECTED ; 
 int /*<<< orphan*/  _glfwFreeJoystick (TYPE_2__*) ; 
 int /*<<< orphan*/  _glfwInputJoystick (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void closeJoystick(_GLFWjoystick* js)
{
    close(js->linjs.fd);
    _glfwFreeJoystick(js);
    _glfwInputJoystick(js, GLFW_DISCONNECTED);
}