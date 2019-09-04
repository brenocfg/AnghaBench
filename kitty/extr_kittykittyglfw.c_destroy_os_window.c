#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * handle; } ;
typedef  TYPE_1__ OSWindow ;

/* Variables and functions */
 int /*<<< orphan*/  glfwDestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSetCursor (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_mouse_cursor (int /*<<< orphan*/ *) ; 

void
destroy_os_window(OSWindow *w) {
#ifdef __APPLE__
    static size_t source_workspaces[64];
    size_t source_workspace_count = 0;
#endif
    if (w->handle) {
#ifdef __APPLE__
        source_workspace_count = cocoa_get_workspace_ids(glfwGetCocoaWindow(w->handle), source_workspaces, arraysz(source_workspaces));
#endif
        // Ensure mouse cursor is visible and reset to default shape, needed on macOS
        show_mouse_cursor(w->handle);
        glfwSetCursor(w->handle, NULL);
        glfwDestroyWindow(w->handle);
    }
    w->handle = NULL;
#ifdef __APPLE__
    // On macOS when closing a window, any other existing windows belonging to the same application do not
    // automatically get focus, so we do it manually.
    cocoa_focus_last_window(w->id, source_workspaces, source_workspace_count);
#endif
}