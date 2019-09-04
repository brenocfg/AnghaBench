#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * callback_os_window; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/ * PyTuple_New (int) ; 
 int /*<<< orphan*/  PyTuple_SET_ITEM (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyUnicode_FromString (char const*) ; 
 int /*<<< orphan*/  Py_CLEAR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WINDOW_CALLBACK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 TYPE_1__ global_state ; 
 int /*<<< orphan*/  on_drop ; 
 int /*<<< orphan*/  request_tick_callback () ; 
 int /*<<< orphan*/  set_callback_window (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
drop_callback(GLFWwindow *w, int count, const char **paths) {
    if (!set_callback_window(w)) return;
    PyObject *p = PyTuple_New(count);
    if (p) {
        for (int i = 0; i < count; i++) PyTuple_SET_ITEM(p, i, PyUnicode_FromString(paths[i]));
        WINDOW_CALLBACK(on_drop, "O", p);
        Py_CLEAR(p);
        request_tick_callback();
    }
    global_state.callback_os_window = NULL;
}