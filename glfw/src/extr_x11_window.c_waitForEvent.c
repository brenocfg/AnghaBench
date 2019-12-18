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
typedef  double uint64_t ;
struct timeval {long const member_0; long const member_1; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_5__ {int const inotify; } ;
struct TYPE_4__ {int /*<<< orphan*/  display; } ;
struct TYPE_6__ {TYPE_2__ linjs; TYPE_1__ x11; } ;
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 int ConnectionNumber (int /*<<< orphan*/ ) ; 
 int const EINTR ; 
 int /*<<< orphan*/  FD_SET (int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 TYPE_3__ _glfw ; 
 scalar_t__ _glfwPlatformGetTimerFrequency () ; 
 double const _glfwPlatformGetTimerValue () ; 
 int const errno ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

__attribute__((used)) static GLFWbool waitForEvent(double* timeout)
{
    fd_set fds;
    const int fd = ConnectionNumber(_glfw.x11.display);
    int count = fd + 1;

#if defined(__linux__)
    if (_glfw.linjs.inotify > fd)
        count = _glfw.linjs.inotify + 1;
#endif
    for (;;)
    {
        FD_ZERO(&fds);
        FD_SET(fd, &fds);
#if defined(__linux__)
        if (_glfw.linjs.inotify > 0)
            FD_SET(_glfw.linjs.inotify, &fds);
#endif

        if (timeout)
        {
            const long seconds = (long) *timeout;
            const long microseconds = (long) ((*timeout - seconds) * 1e6);
            struct timeval tv = { seconds, microseconds };
            const uint64_t base = _glfwPlatformGetTimerValue();

            const int result = select(count, &fds, NULL, NULL, &tv);
            const int error = errno;

            *timeout -= (_glfwPlatformGetTimerValue() - base) /
                (double) _glfwPlatformGetTimerFrequency();

            if (result > 0)
                return GLFW_TRUE;
            if ((result == -1 && error == EINTR) || *timeout <= 0.0)
                return GLFW_FALSE;
        }
        else if (select(count, &fds, NULL, NULL, NULL) != -1 || errno != EINTR)
            return GLFW_TRUE;
    }
}