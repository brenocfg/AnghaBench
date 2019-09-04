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
typedef  int /*<<< orphan*/  id_type ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  ChildMonitor ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  mark_child_for_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
mark_for_close(ChildMonitor *self, PyObject *args) {
#define mark_for_close_doc "Mark a child to be removed from the child monitor"
    id_type window_id;
    if (!PyArg_ParseTuple(args, "K", &window_id)) return NULL;
    mark_child_for_close(self, window_id);
    Py_RETURN_NONE;
}