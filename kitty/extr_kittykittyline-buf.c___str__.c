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
typedef  size_t index_type ;
struct TYPE_4__ {size_t ynum; int /*<<< orphan*/  line; int /*<<< orphan*/ * line_map; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ LineBuf ;

/* Variables and functions */
 int /*<<< orphan*/ * PyErr_NoMemory () ; 
 int /*<<< orphan*/ * PyTuple_New (size_t) ; 
 int /*<<< orphan*/  PyTuple_SET_ITEM (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyUnicode_FromString (char*) ; 
 int /*<<< orphan*/ * PyUnicode_Join (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_CLEAR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_line (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * line_as_unicode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject*
__str__(LineBuf *self) {
    PyObject *lines = PyTuple_New(self->ynum);
    if (lines == NULL) return PyErr_NoMemory();
    for (index_type i = 0; i < self->ynum; i++) {
        init_line(self, self->line, self->line_map[i]);
        PyObject *t = line_as_unicode(self->line);
        if (t == NULL) { Py_CLEAR(lines); return NULL; }
        PyTuple_SET_ITEM(lines, i, t);
    }
    PyObject *sep = PyUnicode_FromString("\n");
    PyObject *ans = PyUnicode_Join(sep, lines);
    Py_CLEAR(lines); Py_CLEAR(sep);
    return ans;
}