#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  fds; } ;
struct TYPE_5__ {TYPE_1__ eventLoopData; } ;
struct TYPE_6__ {TYPE_2__ x11; } ;
typedef  scalar_t__ GLFWbool ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ GLFW_FALSE ; 
 scalar_t__ GLFW_TRUE ; 
 TYPE_3__ _glfw ; 
 scalar_t__ errno ; 
 double glfwGetTime () ; 
 int poll (int /*<<< orphan*/ ,int,int) ; 
 int pollWithTimeout (int /*<<< orphan*/ ,int,double) ; 

__attribute__((used)) static GLFWbool
waitForX11Event(double timeout) {
    // returns true iff there is X11 data waiting to be read, does not run watches and timers
    double end_time = glfwGetTime() + timeout;
    while(GLFW_TRUE) {
        if (timeout >= 0) {
            const int result = pollWithTimeout(_glfw.x11.eventLoopData.fds, 1, timeout);
            if (result > 0) return GLFW_TRUE;
            timeout = end_time - glfwGetTime();
            if (timeout <= 0) return GLFW_FALSE;
            if (result < 0 && (errno == EINTR || errno == EAGAIN)) continue;
            return GLFW_FALSE;
        } else {
            const int result = poll(_glfw.x11.eventLoopData.fds, 1, -1);
            if (result > 0) return GLFW_TRUE;
            if (result < 0 && (errno == EINTR || errno == EAGAIN)) continue;
            return GLFW_FALSE;
        }
    }
}