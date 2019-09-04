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
struct TYPE_3__ {unsigned int ynum; int /*<<< orphan*/ * line_attrs; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ LineBuf ;

/* Variables and functions */
 int /*<<< orphan*/  CONTINUED_MASK ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,unsigned int*,int*) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 

__attribute__((used)) static PyObject*
set_continued(LineBuf *self, PyObject *args) {
#define set_continued_doc "set_continued(y, val) -> Set the continued values for the specified line."
    unsigned int y;
    int val;
    if (!PyArg_ParseTuple(args, "Ip", &y, &val)) return NULL;
    if (y >= self->ynum) { PyErr_SetString(PyExc_ValueError, "Out of bounds."); return NULL; }
    if (val) self->line_attrs[y] |= CONTINUED_MASK;
    else self->line_attrs[y] &= ~CONTINUED_MASK;
    Py_RETURN_NONE;
}