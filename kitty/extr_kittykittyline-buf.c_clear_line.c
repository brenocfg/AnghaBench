#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ index_type ;
struct TYPE_4__ {scalar_t__ ynum; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ LineBuf ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  PyLong_AsUnsignedLong (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  linebuf_clear_line (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static PyObject*
clear_line(LineBuf *self, PyObject *val) {
#define clear_line_doc "clear_line(y) -> Clear the specified line"
    index_type y = (index_type)PyLong_AsUnsignedLong(val);
    if (y >= self->ynum) { PyErr_SetString(PyExc_ValueError, "Out of bounds"); return NULL; }
    linebuf_clear_line(self, y);
    Py_RETURN_NONE;
}