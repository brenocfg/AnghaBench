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
struct TYPE_3__ {int /*<<< orphan*/  eventLoopData; } ;
struct TYPE_4__ {TYPE_1__ GLFW_LOOP_BACKEND; } ;
typedef  int /*<<< orphan*/  GLFWuserdatafreefun ;

/* Variables and functions */
 TYPE_2__ _glfw ; 
 unsigned long long addTimer (int /*<<< orphan*/ *,char*,double,int,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

unsigned long long _glfwPlatformAddTimer(double interval, bool repeats, GLFWuserdatafreefun callback, void *callback_data, GLFWuserdatafreefun free_callback) {
    return addTimer(&_glfw.GLFW_LOOP_BACKEND.eventLoopData, "user timer", interval, 1, repeats, callback, callback_data, free_callback);
}