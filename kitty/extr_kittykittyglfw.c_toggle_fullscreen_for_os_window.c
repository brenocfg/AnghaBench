#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int width; int height; int /*<<< orphan*/  refreshRate; } ;
struct TYPE_6__ {int is_set; int w; int h; int x; int y; } ;
struct TYPE_7__ {int /*<<< orphan*/  handle; TYPE_1__ before_fullscreen; } ;
typedef  TYPE_2__ OSWindow ;
typedef  TYPE_3__ GLFWvidmode ;
typedef  int /*<<< orphan*/  GLFWmonitor ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_Print () ; 
 int /*<<< orphan*/ * current_monitor (int /*<<< orphan*/ ) ; 
 TYPE_3__* glfwGetVideoMode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * glfwGetWindowMonitor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwGetWindowPos (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  glfwGetWindowSize (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  glfwSetWindowMonitor (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
toggle_fullscreen_for_os_window(OSWindow *w) {
    int width, height, x, y;
    glfwGetWindowSize(w->handle, &width, &height);
    glfwGetWindowPos(w->handle, &x, &y);
#ifdef __APPLE__
    if (OPT(macos_traditional_fullscreen)) {
        if (cocoa_toggle_fullscreen(glfwGetCocoaWindow(w->handle), true)) {
            w->before_fullscreen.is_set = true;
            w->before_fullscreen.w = width; w->before_fullscreen.h = height; w->before_fullscreen.x = x; w->before_fullscreen.y = y;
            return true;
        }
        if (w->before_fullscreen.is_set) {
            glfwSetWindowSize(w->handle, w->before_fullscreen.w, w->before_fullscreen.h);
            glfwSetWindowPos(w->handle, w->before_fullscreen.x, w->before_fullscreen.y);
        }
        return false;
    } else {
        return cocoa_toggle_fullscreen(glfwGetCocoaWindow(w->handle), false);
    }
#else
    GLFWmonitor *monitor;
    if ((monitor = glfwGetWindowMonitor(w->handle)) == NULL) {
        // make fullscreen
        monitor = current_monitor(w->handle);
        if (monitor == NULL) { PyErr_Print(); return false; }
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        w->before_fullscreen.is_set = true;
        w->before_fullscreen.w = width; w->before_fullscreen.h = height; w->before_fullscreen.x = x; w->before_fullscreen.y = y;
        glfwGetWindowSize(w->handle, &w->before_fullscreen.w, &w->before_fullscreen.h);
        glfwGetWindowPos(w->handle, &w->before_fullscreen.x, &w->before_fullscreen.y);
        glfwSetWindowMonitor(w->handle, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        return true;
    } else {
        // make windowed
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        if (w->before_fullscreen.is_set) glfwSetWindowMonitor(w->handle, NULL, w->before_fullscreen.x, w->before_fullscreen.y, w->before_fullscreen.w, w->before_fullscreen.h, mode->refreshRate);
        else glfwSetWindowMonitor(w->handle, NULL, 0, 0, 600, 400, mode->refreshRate);
        return false;
    }
#endif
}