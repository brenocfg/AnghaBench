#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int viewport_width; int viewport_height; int window_width; int window_height; double viewport_x_ratio; double viewport_y_ratio; double logical_dpi_x; double logical_dpi_y; int viewport_size_dirty; int /*<<< orphan*/  id; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ OSWindow ;

/* Variables and functions */
 void* MAX (int,int) ; 
 int /*<<< orphan*/  Py_False ; 
 int /*<<< orphan*/  Py_True ; 
 int /*<<< orphan*/  call_boss (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwGetFramebufferSize (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  glfwGetWindowSize (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  on_window_resize ; 
 int /*<<< orphan*/  set_os_window_dpi (TYPE_1__*) ; 

void
update_os_window_viewport(OSWindow *window, bool notify_boss) {
    int w, h, fw, fh;
    glfwGetFramebufferSize(window->handle, &fw, &fh);
    glfwGetWindowSize(window->handle, &w, &h);
    if (fw == window->viewport_width && fh == window->viewport_height && w == window->window_width && h == window->window_height) {
        return; // no change, ignore
    }
    window->viewport_width = fw; window->viewport_height = fh;
    double xr = window->viewport_x_ratio, yr = window->viewport_y_ratio;
    window->viewport_x_ratio = w > 0 ? (double)window->viewport_width / (double)w : xr;
    window->viewport_y_ratio = h > 0 ? (double)window->viewport_height / (double)h : yr;
    double xdpi = window->logical_dpi_x, ydpi = window->logical_dpi_y;
    set_os_window_dpi(window);
    bool dpi_changed = (xr != 0.0 && xr != window->viewport_x_ratio) || (yr != 0.0 && yr != window->viewport_y_ratio) || (xdpi != window->logical_dpi_x) || (ydpi != window->logical_dpi_y);

    window->viewport_size_dirty = true;
    window->viewport_width = MAX(window->viewport_width, 100);
    window->viewport_height = MAX(window->viewport_height, 100);
    window->window_width = MAX(w, 100);
    window->window_height = MAX(h, 100);
    if (notify_boss) {
        call_boss(on_window_resize, "KiiO", window->id, window->viewport_width, window->viewport_height, dpi_changed ? Py_True : Py_False);
    }
}