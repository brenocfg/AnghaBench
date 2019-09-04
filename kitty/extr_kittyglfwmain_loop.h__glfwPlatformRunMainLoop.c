#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  (* GLFWtickcallback ) (void*) ;

/* Variables and functions */
 int /*<<< orphan*/  EVDBG (char*) ; 
 scalar_t__ GLFW_TRUE ; 
 int /*<<< orphan*/  _glfwPlatformWaitEvents () ; 
 scalar_t__ keep_going ; 

void _glfwPlatformRunMainLoop(GLFWtickcallback tick_callback, void* data) {
    keep_going = GLFW_TRUE;
    while(keep_going) {
        _glfwPlatformWaitEvents();
		EVDBG("loop tick");
        tick_callback(data);
    }
}