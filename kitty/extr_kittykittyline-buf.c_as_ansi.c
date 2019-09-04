#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t index_type ;
struct TYPE_8__ {int continued; int /*<<< orphan*/  xnum; } ;
struct TYPE_7__ {int ynum; int* line_attrs; int /*<<< orphan*/ * line_map; int /*<<< orphan*/  xnum; } ;
typedef  int Py_UCS4 ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ LineBuf ;
typedef  TYPE_2__ Line ;

/* Variables and functions */
 int CONTINUED_MASK ; 
 int /*<<< orphan*/ * PyErr_NoMemory () ; 
 int /*<<< orphan*/ * PyObject_CallFunctionObjArgs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyUnicode_4BYTE_KIND ; 
 int /*<<< orphan*/ * PyUnicode_FromKindAndData (int /*<<< orphan*/ ,int*,size_t) ; 
 int /*<<< orphan*/  Py_CLEAR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  init_line (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ line_as_ansi (TYPE_2__*,int*,int,int*) ; 

__attribute__((used)) static PyObject*
as_ansi(LineBuf *self, PyObject *callback) {
#define as_ansi_doc "as_ansi(callback) -> The contents of this buffer as ANSI escaped text. callback is called with each successive line."
    static Py_UCS4 t[5120];
    Line l = {.xnum=self->xnum};
    // remove trailing empty lines
    index_type ylimit = self->ynum - 1;
    bool truncated;
    do {
        init_line(self, (&l), self->line_map[ylimit]);
        if (line_as_ansi(&l, t, 5120, &truncated) != 0) break;
        ylimit--;
    } while(ylimit > 0);

    for(index_type i = 0; i <= ylimit; i++) {
        l.continued = ((i < self->ynum - 1) ? self->line_attrs[i+1] : self->line_attrs[i]) & CONTINUED_MASK;
        init_line(self, (&l), self->line_map[i]);
        index_type num = line_as_ansi(&l, t, 5120, &truncated);
        if (!(l.continued) && num < 5119) t[num++] = 10; // 10 = \n
        PyObject *ans = PyUnicode_FromKindAndData(PyUnicode_4BYTE_KIND, t, num);
        if (ans == NULL) return PyErr_NoMemory();
        PyObject *ret = PyObject_CallFunctionObjArgs(callback, ans, NULL);
        Py_CLEAR(ans);
        if (ret == NULL) return NULL;
        Py_CLEAR(ret);
    }
    Py_RETURN_NONE;
}