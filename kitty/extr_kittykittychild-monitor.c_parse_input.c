#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int terminate; int /*<<< orphan*/  boss; } ;
struct TYPE_15__ {int /*<<< orphan*/  id; } ;
struct TYPE_14__ {int /*<<< orphan*/  screen; int /*<<< orphan*/  needs_removal; } ;
struct TYPE_13__ {size_t messages_count; size_t count; int /*<<< orphan*/  death_notify; TYPE_1__* messages; } ;
struct TYPE_12__ {scalar_t__ sz; int /*<<< orphan*/ * data; int /*<<< orphan*/  fd; } ;
typedef  scalar_t__ Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ Message ;
typedef  TYPE_2__ ChildMonitor ;

/* Variables and functions */
 int /*<<< orphan*/  DECREF_CHILD (TYPE_3__) ; 
 int /*<<< orphan*/  FREE_CHILD (TYPE_4__) ; 
 int /*<<< orphan*/  INCREF_CHILD (TYPE_3__) ; 
 int /*<<< orphan*/ * PyBytes_AS_STRING (int /*<<< orphan*/ *) ; 
 scalar_t__ PyBytes_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyBytes_GET_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_Print () ; 
 scalar_t__ PyLong_AsLong (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyObject_CallFunction (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyObject_CallMethod (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyTuple_GET_ITEM (int /*<<< orphan*/ *,int) ; 
 scalar_t__ PyTuple_GET_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyTuple_New (size_t) ; 
 int /*<<< orphan*/  PyTuple_SET_ITEM (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_BuildValue (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_CLEAR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 scalar_t__ UNLIKELY (size_t) ; 
 TYPE_3__* children ; 
 int /*<<< orphan*/  children_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_parse (TYPE_2__*,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_6__ global_state ; 
 size_t kill_signal_received ; 
 int /*<<< orphan*/  lock ; 
 double monotonic () ; 
 int /*<<< orphan*/ * remove_notify ; 
 TYPE_4__* remove_queue ; 
 int remove_queue_count ; 
 TYPE_3__* scratch ; 
 int /*<<< orphan*/  send_response (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock ; 

__attribute__((used)) static void
parse_input(ChildMonitor *self) {
    // Parse all available input that was read in the I/O thread.
    size_t count = 0, remove_count = 0;
    double now = monotonic();
    PyObject *msg = NULL;
    children_mutex(lock);
    while (remove_queue_count) {
        remove_queue_count--;
        remove_notify[remove_count] = remove_queue[remove_queue_count].id;
        remove_count++;
        FREE_CHILD(remove_queue[remove_queue_count]);
    }

    if (UNLIKELY(self->messages_count)) {
        msg = PyTuple_New(self->messages_count);
        if (msg) {
            for (size_t i = 0; i < self->messages_count; i++) {
                Message *m = self->messages + i;
                PyTuple_SET_ITEM(msg, i, Py_BuildValue("y#i", m->data, (int)m->sz, m->fd));
                free(m->data); m->data = NULL; m->sz = 0;
            }
            self->messages_count = 0;
        } else fatal("Out of memory");
    }

    if (UNLIKELY(kill_signal_received)) {
        global_state.terminate = true;
    } else {
        count = self->count;
        for (size_t i = 0; i < count; i++) {
            scratch[i] = children[i];
            INCREF_CHILD(scratch[i]);
        }
    }
    children_mutex(unlock);
    if (msg) {
        for (Py_ssize_t i = 0; i < PyTuple_GET_SIZE(msg); i++) {
            PyObject *resp = PyObject_CallMethod(global_state.boss, "peer_message_received", "O", PyTuple_GET_ITEM(PyTuple_GET_ITEM(msg, i), 0));
            int peer_fd = (int)PyLong_AsLong(PyTuple_GET_ITEM(PyTuple_GET_ITEM(msg, i), 1));
            if (resp && PyBytes_Check(resp)) send_response(peer_fd, PyBytes_AS_STRING(resp), PyBytes_GET_SIZE(resp));
            else { send_response(peer_fd, NULL, 0); if (!resp) PyErr_Print(); }
            Py_CLEAR(resp);
        }
        Py_CLEAR(msg);
    }

    while(remove_count) {
        // must be done while no locks are held, since the locks are non-recursive and
        // the python function could call into other functions in this module
        remove_count--;
        PyObject *t = PyObject_CallFunction(self->death_notify, "k", remove_notify[remove_count]);
        if (t == NULL) PyErr_Print();
        else Py_DECREF(t);
    }

    for (size_t i = 0; i < count; i++) {
        if (!scratch[i].needs_removal) {
            do_parse(self, scratch[i].screen, now);
        }
        DECREF_CHILD(scratch[i]);
    }
}