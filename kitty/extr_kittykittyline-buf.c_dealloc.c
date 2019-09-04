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
struct TYPE_5__ {int /*<<< orphan*/  line; int /*<<< orphan*/  scratch; int /*<<< orphan*/  line_attrs; int /*<<< orphan*/  line_map; int /*<<< orphan*/  gpu_cell_buf; int /*<<< orphan*/  cpu_cell_buf; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ LineBuf ;

/* Variables and functions */
 int /*<<< orphan*/  PyMem_Free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_CLEAR (int /*<<< orphan*/ ) ; 
 TYPE_3__* Py_TYPE (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dealloc(LineBuf* self) {
    PyMem_Free(self->cpu_cell_buf);
    PyMem_Free(self->gpu_cell_buf);
    PyMem_Free(self->line_map);
    PyMem_Free(self->line_attrs);
    PyMem_Free(self->scratch);
    Py_CLEAR(self->line);
    Py_TYPE(self)->tp_free((PyObject*)self);
}