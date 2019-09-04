#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* tp_free ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  death_notify; int /*<<< orphan*/  dump_callback; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ ChildMonitor ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_CHILD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_CLEAR (int /*<<< orphan*/ ) ; 
 TYPE_3__* Py_TYPE (TYPE_1__*) ; 
 int /*<<< orphan*/ * add_queue ; 
 int add_queue_count ; 
 int /*<<< orphan*/  children_lock ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * remove_queue ; 
 int remove_queue_count ; 
 int /*<<< orphan*/ * signal_fds ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wakeup_fds ; 

__attribute__((used)) static void
dealloc(ChildMonitor* self) {
    pthread_mutex_destroy(&children_lock);
    Py_CLEAR(self->dump_callback);
    Py_CLEAR(self->death_notify);
    Py_TYPE(self)->tp_free((PyObject*)self);
    while (remove_queue_count) {
        remove_queue_count--;
        FREE_CHILD(remove_queue[remove_queue_count]);
    }
    while (add_queue_count) {
        add_queue_count--;
        FREE_CHILD(add_queue[add_queue_count]);
    }
    close(wakeup_fds[0]);
    close(wakeup_fds[1]);
    close(signal_fds[0]);
    close(signal_fds[1]);
}