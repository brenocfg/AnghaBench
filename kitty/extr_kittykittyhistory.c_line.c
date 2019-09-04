#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ index_type ;
struct TYPE_5__ {scalar_t__ count; scalar_t__ line; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ HistoryBuf ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_IndexError ; 
 scalar_t__ PyLong_AsUnsignedLong (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (scalar_t__) ; 
 int /*<<< orphan*/  index_of (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  init_line (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static PyObject*
line(HistoryBuf *self, PyObject *val) {
#define line_doc "Return the line with line number val. This buffer grows upwards, i.e. 0 is the most recently added line"
    if (self->count == 0) { PyErr_SetString(PyExc_IndexError, "This buffer is empty"); return NULL; }
    index_type lnum = PyLong_AsUnsignedLong(val);
    if (lnum >= self->count) { PyErr_SetString(PyExc_IndexError, "Out of bounds"); return NULL; }
    init_line(self, index_of(self, lnum), self->line);
    Py_INCREF(self->line);
    return (PyObject*)self->line;
}