#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int index_type ;
struct TYPE_10__ {unsigned int count; int /*<<< orphan*/  xnum; } ;
struct TYPE_9__ {int continued; int /*<<< orphan*/  xnum; } ;
typedef  int Py_UCS4 ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ Line ;
typedef  TYPE_2__ HistoryBuf ;

/* Variables and functions */
 int CONTINUED_MASK ; 
 int /*<<< orphan*/ * PyErr_NoMemory () ; 
 int /*<<< orphan*/ * PyObject_CallFunctionObjArgs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyUnicode_4BYTE_KIND ; 
 int /*<<< orphan*/ * PyUnicode_FromKindAndData (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  Py_CLEAR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int* attrptr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_of (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  init_line (TYPE_2__*,unsigned int,TYPE_1__*) ; 
 int line_as_ansi (TYPE_1__*,int*,int,int*) ; 

__attribute__((used)) static PyObject*
as_ansi(HistoryBuf *self, PyObject *callback) {
#define as_ansi_doc "as_ansi(callback) -> The contents of this buffer as ANSI escaped text. callback is called with each successive line."
    static Py_UCS4 t[5120];
    Line l = {.xnum=self->xnum};
    bool truncated;
    for(unsigned int i = 0; i < self->count; i++) {
        init_line(self, i, &l);
        if (i < self->count - 1) {
            l.continued = *attrptr(self, index_of(self, i + 1)) & CONTINUED_MASK;
        } else l.continued = false;
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