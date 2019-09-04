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
struct TYPE_3__ {unsigned long ynum; int* line_attrs; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ LineBuf ;

/* Variables and functions */
 int CONTINUED_MASK ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 unsigned long PyLong_AsUnsignedLong (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_RETURN_FALSE ; 
 int /*<<< orphan*/  Py_RETURN_TRUE ; 

__attribute__((used)) static PyObject*
is_continued(LineBuf *self, PyObject *val) {
#define is_continued_doc "is_continued(y) -> Whether the line y is continued or not"
    unsigned long y = PyLong_AsUnsignedLong(val);
    if (y >= self->ynum) { PyErr_SetString(PyExc_ValueError, "Out of bounds."); return NULL; }
    if (self->line_attrs[y] & CONTINUED_MASK) { Py_RETURN_TRUE; }
    Py_RETURN_FALSE;
}