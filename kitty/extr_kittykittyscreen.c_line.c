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
struct TYPE_5__ {scalar_t__ line; } ;
struct TYPE_4__ {unsigned long lines; TYPE_2__* linebuf; } ;
typedef  TYPE_1__ Screen ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_IndexError ; 
 unsigned long PyLong_AsUnsignedLong (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (scalar_t__) ; 
 int /*<<< orphan*/  linebuf_init_line (TYPE_2__*,unsigned long) ; 

__attribute__((used)) static PyObject*
line(Screen *self, PyObject *val) {
    unsigned long y = PyLong_AsUnsignedLong(val);
    if (y >= self->lines) { PyErr_SetString(PyExc_IndexError, "Out of bounds"); return NULL; }
    linebuf_init_line(self->linebuf, y);
    Py_INCREF(self->linebuf->line);
    return (PyObject*) self->linebuf->line;
}