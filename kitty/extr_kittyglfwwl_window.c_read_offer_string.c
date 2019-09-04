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
struct pollfd {int fd; int /*<<< orphan*/  events; } ;
struct TYPE_3__ {int /*<<< orphan*/  display; } ;
struct TYPE_4__ {TYPE_1__ wl; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  POLLIN ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 double glfwGetTime () ; 
 int poll (struct pollfd*,int,int) ; 
 int read (int,char*,size_t) ; 
 char* realloc (char*,size_t) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  wl_display_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char* read_offer_string(int data_pipe) {
    wl_display_flush(_glfw.wl.display);
    size_t sz = 0, capacity = 0;
    char *buf = NULL;
    struct pollfd fds;
    fds.fd = data_pipe;
    fds.events = POLLIN;
    double start = glfwGetTime();
#define bail(...) { \
    _glfwInputError(GLFW_PLATFORM_ERROR, __VA_ARGS__); \
    free(buf); buf = NULL; \
    close(data_pipe); \
    return NULL; \
}

    while (glfwGetTime() - start < 2) {
        int ret = poll(&fds, 1, 2000);
        if (ret == -1) {
            if (errno == EINTR) continue;
            bail("Wayland: Failed to poll clipboard data from pipe with error: %s", strerror(errno));
        }
        if (!ret) {
            bail("Wayland: Failed to read clipboard data from pipe (timed out)");
        }
        if (capacity <= sz || capacity - sz <= 64) {
            capacity += 4096;
            buf = realloc(buf, capacity);
            if (!buf) {
                bail("Wayland: Failed to allocate memory to read clipboard data");
            }
        }
        ret = read(data_pipe, buf + sz, capacity - sz - 1);
        if (ret == -1) {
            if (errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK) continue;
            bail("Wayland: Failed to read clipboard data from pipe with error: %s", strerror(errno));
        }
        if (ret == 0) { close(data_pipe); buf[sz] = 0; return buf; }
        sz += ret;
        start = glfwGetTime();
    }
    bail("Wayland: Failed to read clipboard data from pipe (timed out)");
#undef bail

}