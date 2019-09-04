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
struct TYPE_4__ {unsigned long ynum; scalar_t__ line; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ LineBuf ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_IndexError ; 
 unsigned long PyLong_AsUnsignedLong (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (scalar_t__) ; 
 int /*<<< orphan*/  linebuf_init_line (TYPE_1__*,unsigned long) ; 

__attribute__((used)) static PyObject*
line(LineBuf *self, PyObject *y) {
#define line_doc      "Return the specified line as a Line object. Note the Line Object is a live view into the underlying buffer. And only a single line object can be used at a time."
    unsigned long idx = PyLong_AsUnsignedLong(y);
    if (idx >= self->ynum) {
        PyErr_SetString(PyExc_IndexError, "Line number too large");
        return NULL;
    }
    linebuf_init_line(self, idx);
    Py_INCREF(self->line);
    return (PyObject*)self->line;
}