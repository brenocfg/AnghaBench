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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 double glfwGetTime () ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 size_t strlen (char*) ; 
 scalar_t__ write (int,char*,size_t) ; 

__attribute__((used)) static void send_text(char *text, int fd)
{
    if (text) {
        size_t len = strlen(text), pos = 0;
        double start = glfwGetTime();
        while (pos < len && glfwGetTime() - start < 2.0) {
            ssize_t ret = write(fd, text + pos, len - pos);
            if (ret < 0) {
                if (errno == EAGAIN || errno == EINTR) continue;
                _glfwInputError(GLFW_PLATFORM_ERROR,
                    "Wayland: Could not copy writing to destination fd failed with error: %s", strerror(errno));
                break;
            }
            if (ret > 0) {
                start = glfwGetTime();
                pos += ret;
            }
        }
    }
    close(fd);
}