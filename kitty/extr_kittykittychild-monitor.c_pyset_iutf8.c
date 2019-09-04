#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned long id; } ;
struct TYPE_6__ {int /*<<< orphan*/  fd; } ;
struct TYPE_5__ {size_t count; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ ChildMonitor ;

/* Variables and functions */
 size_t EXTRA_FDS ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,unsigned long*,int*) ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/  PyErr_SetFromErrno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_OSError ; 
 int /*<<< orphan*/ * Py_False ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_True ; 
 TYPE_4__* children ; 
 int /*<<< orphan*/  children_mutex (int /*<<< orphan*/ ) ; 
 TYPE_3__* fds ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  set_iutf8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unlock ; 

__attribute__((used)) static PyObject*
pyset_iutf8(ChildMonitor *self, PyObject *args) {
    unsigned long window_id;
    int on;
    PyObject *found = Py_False;
    if (!PyArg_ParseTuple(args, "kp", &window_id, &on)) return NULL;
    children_mutex(lock);
    for (size_t i = 0; i < self->count; i++) {
        if (children[i].id == window_id) {
            found = Py_True;
            if (!set_iutf8(fds[EXTRA_FDS + i].fd, on & 1)) PyErr_SetFromErrno(PyExc_OSError);
            break;
        }
    }
    children_mutex(unlock);
    if (PyErr_Occurred()) return NULL;
    Py_INCREF(found);
    return found;
}