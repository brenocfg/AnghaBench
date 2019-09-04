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
struct TYPE_5__ {int /*<<< orphan*/  gpu_cells; int /*<<< orphan*/  cpu_cells; scalar_t__ needs_free; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ Line ;

/* Variables and functions */
 int /*<<< orphan*/  PyMem_Free (int /*<<< orphan*/ ) ; 
 TYPE_3__* Py_TYPE (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dealloc(Line* self) {
    if (self->needs_free) {
        PyMem_Free(self->cpu_cells);
        PyMem_Free(self->gpu_cells);
    }
    Py_TYPE(self)->tp_free((PyObject*)self);
}