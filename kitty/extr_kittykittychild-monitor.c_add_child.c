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
struct TYPE_7__ {int /*<<< orphan*/  screen; int /*<<< orphan*/  fd; int /*<<< orphan*/  pid; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {scalar_t__ count; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ ChildMonitor ;

/* Variables and functions */
 TYPE_2__ EMPTY_CHILD ; 
 int /*<<< orphan*/  INCREF_CHILD (TYPE_2__) ; 
 scalar_t__ MAX_CHILDREN ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 TYPE_2__* add_queue ; 
 size_t add_queue_count ; 
 int /*<<< orphan*/  children_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  unlock ; 
 int /*<<< orphan*/  wakeup_io_loop (int) ; 

__attribute__((used)) static PyObject *
add_child(ChildMonitor *self, PyObject *args) {
#define add_child_doc "add_child(id, pid, fd, screen) -> Add a child."
    children_mutex(lock);
    if (self->count + add_queue_count >= MAX_CHILDREN) { PyErr_SetString(PyExc_ValueError, "Too many children"); children_mutex(unlock); return NULL; }
    add_queue[add_queue_count] = EMPTY_CHILD;
#define A(attr) &add_queue[add_queue_count].attr
    if (!PyArg_ParseTuple(args, "kiiO", A(id), A(pid), A(fd), A(screen))) {
        children_mutex(unlock);
        return NULL;
    }
#undef A
    INCREF_CHILD(add_queue[add_queue_count]);
    add_queue_count++;
    children_mutex(unlock);
    wakeup_io_loop(false);
    Py_RETURN_NONE;
}