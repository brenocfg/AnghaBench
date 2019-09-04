#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  (* tp_free ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  buf; } ;
struct TYPE_7__ {int /*<<< orphan*/  gpu_cells; int /*<<< orphan*/  cpu_cells; } ;
struct TYPE_9__ {TYPE_2__ pending_mode; int /*<<< orphan*/  main_tabstops; TYPE_1__ overlay_line; int /*<<< orphan*/  color_profile; int /*<<< orphan*/  historybuf; int /*<<< orphan*/  alt_linebuf; int /*<<< orphan*/  main_linebuf; int /*<<< orphan*/  cursor; int /*<<< orphan*/  test_child; int /*<<< orphan*/  callbacks; int /*<<< orphan*/  write_buf; int /*<<< orphan*/  alt_grman; int /*<<< orphan*/  main_grman; int /*<<< orphan*/  write_buf_lock; int /*<<< orphan*/  read_buf_lock; } ;
typedef  TYPE_3__ Screen ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyMem_Free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyMem_RawFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_CLEAR (int /*<<< orphan*/ ) ; 
 TYPE_5__* Py_TYPE (TYPE_3__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dealloc(Screen* self) {
    pthread_mutex_destroy(&self->read_buf_lock);
    pthread_mutex_destroy(&self->write_buf_lock);
    Py_CLEAR(self->main_grman);
    Py_CLEAR(self->alt_grman);
    PyMem_RawFree(self->write_buf);
    Py_CLEAR(self->callbacks);
    Py_CLEAR(self->test_child);
    Py_CLEAR(self->cursor);
    Py_CLEAR(self->main_linebuf);
    Py_CLEAR(self->alt_linebuf);
    Py_CLEAR(self->historybuf);
    Py_CLEAR(self->color_profile);
    PyMem_Free(self->overlay_line.cpu_cells);
    PyMem_Free(self->overlay_line.gpu_cells);
    PyMem_Free(self->main_tabstops);
    free(self->pending_mode.buf);
    Py_TYPE(self)->tp_free((PyObject*)self);
}