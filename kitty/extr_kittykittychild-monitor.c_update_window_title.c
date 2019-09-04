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
struct TYPE_6__ {scalar_t__ title; } ;
typedef  TYPE_1__ Window ;
struct TYPE_7__ {scalar_t__ window_title; } ;
typedef  TYPE_2__ OSWindow ;

/* Variables and functions */
 int /*<<< orphan*/  PyUnicode_AsUTF8 (scalar_t__) ; 
 int /*<<< orphan*/  Py_INCREF (scalar_t__) ; 
 int /*<<< orphan*/  set_os_window_title (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
update_window_title(Window *w, OSWindow *os_window) {
    if (w->title && w->title != os_window->window_title) {
        os_window->window_title = w->title;
        Py_INCREF(os_window->window_title);
        set_os_window_title(os_window, PyUnicode_AsUTF8(w->title));
#ifdef __APPLE__
        if (os_window->is_focused && OPT(macos_show_window_title_in_menubar)) cocoa_update_title(w->title);
#endif
        return true;
    }
    return false;
}