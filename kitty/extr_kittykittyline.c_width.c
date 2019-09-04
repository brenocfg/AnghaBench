#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int char_type ;
struct TYPE_5__ {unsigned long xnum; TYPE_1__* gpu_cells; } ;
struct TYPE_4__ {int attrs; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ Line ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 unsigned long PyLong_AsUnsignedLong (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyLong_FromUnsignedLong (unsigned long) ; 
 int WIDTH_MASK ; 

__attribute__((used)) static PyObject*
width(Line *self, PyObject *val) {
#define width_doc "width(x) -> the width of the character at x"
    unsigned long x = PyLong_AsUnsignedLong(val);
    if (x >= self->xnum) { PyErr_SetString(PyExc_ValueError, "Out of bounds"); return NULL; }
    char_type attrs = self->gpu_cells[x].attrs;
    return PyLong_FromUnsignedLong((unsigned long) (attrs & WIDTH_MASK));
}