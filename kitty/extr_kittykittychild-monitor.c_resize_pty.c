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
struct winsize {int /*<<< orphan*/  ws_ypixel; int /*<<< orphan*/  ws_xpixel; int /*<<< orphan*/  ws_col; int /*<<< orphan*/  ws_row; } ;
struct TYPE_7__ {unsigned long id; int fd; } ;
struct TYPE_6__ {unsigned long id; int fd; } ;
struct TYPE_5__ {size_t count; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ ChildMonitor ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,unsigned long*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/  PyErr_SetFromErrno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_OSError ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 TYPE_4__* add_queue ; 
 size_t add_queue_count ; 
 TYPE_3__* children ; 
 int /*<<< orphan*/  children_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  log_error (char*,unsigned long,size_t,size_t) ; 
 int /*<<< orphan*/  pty_resize (int,struct winsize*) ; 
 int /*<<< orphan*/  unlock ; 

__attribute__((used)) static PyObject *
resize_pty(ChildMonitor *self, PyObject *args) {
#define resize_pty_doc "Resize the pty associated with the specified child"
    unsigned long window_id;
    struct winsize dim;
    int fd = -1;
    if (!PyArg_ParseTuple(args, "kHHHH", &window_id, &dim.ws_row, &dim.ws_col, &dim.ws_xpixel, &dim.ws_ypixel)) return NULL;
    children_mutex(lock);
#define FIND(queue, count) { \
    for (size_t i = 0; i < count; i++) { \
        if (queue[i].id == window_id) { \
            fd = queue[i].fd; \
            break; \
        } \
    }}
    FIND(children, self->count);
    if (fd == -1) FIND(add_queue, add_queue_count);
    if (fd != -1) {
        if (!pty_resize(fd, &dim)) PyErr_SetFromErrno(PyExc_OSError);
    } else log_error("Failed to send resize signal to child with id: %lu (children count: %u) (add queue: %zu)", window_id, self->count, add_queue_count);
    children_mutex(unlock);
    if (PyErr_Occurred()) return NULL;
    Py_RETURN_NONE;
}