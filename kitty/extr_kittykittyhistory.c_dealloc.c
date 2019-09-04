#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* line_attrs; struct TYPE_9__* gpu_cells; struct TYPE_9__* cpu_cells; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* tp_free ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {size_t num_segments; TYPE_6__* segments; int /*<<< orphan*/  line; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ HistoryBuf ;

/* Variables and functions */
 int /*<<< orphan*/  PyMem_Free (TYPE_6__*) ; 
 int /*<<< orphan*/  Py_CLEAR (int /*<<< orphan*/ ) ; 
 TYPE_4__* Py_TYPE (TYPE_1__*) ; 
 int /*<<< orphan*/  free_pagerhist (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dealloc(HistoryBuf* self) {
    Py_CLEAR(self->line);
    for (size_t i = 0; i < self->num_segments; i++) {
        PyMem_Free(self->segments[i].cpu_cells);
        PyMem_Free(self->segments[i].gpu_cells);
        PyMem_Free(self->segments[i].line_attrs);
    }
    PyMem_Free(self->segments);
    free_pagerhist(self);
    Py_TYPE(self)->tp_free((PyObject*)self);
}