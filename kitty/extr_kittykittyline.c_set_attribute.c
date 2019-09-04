#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  xnum; int /*<<< orphan*/  gpu_cells; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ Line ;

/* Variables and functions */
 unsigned int DECORATION_SHIFT ; 
 unsigned int DIM_SHIFT ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  set_attribute_on_line (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject*
set_attribute(Line *self, PyObject *args) {
#define set_attribute_doc "set_attribute(which, val) -> Set the attribute on all cells in the line."
    unsigned int shift, val;
    if (!PyArg_ParseTuple(args, "II", &shift, &val)) return NULL;
    if (shift < DECORATION_SHIFT || shift > DIM_SHIFT) { PyErr_SetString(PyExc_ValueError, "Unknown attribute"); return NULL; }
    set_attribute_on_line(self->gpu_cells, shift, val, self->xnum);
    Py_RETURN_NONE;
}