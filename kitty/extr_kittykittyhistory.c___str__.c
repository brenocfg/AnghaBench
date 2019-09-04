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
struct TYPE_5__ {scalar_t__ count; int /*<<< orphan*/  line; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ HistoryBuf ;

/* Variables and functions */
 int /*<<< orphan*/ * PyErr_NoMemory () ; 
 int /*<<< orphan*/ * PyTuple_New (scalar_t__) ; 
 int /*<<< orphan*/  PyTuple_SET_ITEM (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyUnicode_FromString (char*) ; 
 int /*<<< orphan*/ * PyUnicode_Join (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_CLEAR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  index_of (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  init_line (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * line_as_unicode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject*
__str__(HistoryBuf *self) {
    PyObject *lines = PyTuple_New(self->count);
    if (lines == NULL) return PyErr_NoMemory();
    for (index_type i = 0; i < self->count; i++) {
        init_line(self, index_of(self, i), self->line);
        PyObject *t = line_as_unicode(self->line);
        if (t == NULL) { Py_CLEAR(lines); return NULL; }
        PyTuple_SET_ITEM(lines, i, t);
    }
    PyObject *sep = PyUnicode_FromString("\n");
    PyObject *ans = PyUnicode_Join(sep, lines);
    Py_CLEAR(lines); Py_CLEAR(sep);
    return ans;
}