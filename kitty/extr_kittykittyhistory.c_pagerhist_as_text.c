#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int index_type ;
struct TYPE_10__ {int /*<<< orphan*/  xnum; TYPE_1__* pagerhist; } ;
struct TYPE_9__ {int /*<<< orphan*/  continued; int /*<<< orphan*/  xnum; } ;
struct TYPE_8__ {int bufend; int end; int start; int /*<<< orphan*/ * buffer; scalar_t__ rewrap_needed; } ;
typedef  int /*<<< orphan*/  Py_UCS4 ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PagerHistoryBuf ;
typedef  TYPE_2__ Line ;
typedef  TYPE_3__ HistoryBuf ;

/* Variables and functions */
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/ * PyObject_CallFunctionObjArgs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyUnicode_4BYTE_KIND ; 
 int /*<<< orphan*/ * PyUnicode_FromKindAndData (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * PyUnicode_FromString (char*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  get_line (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  pagerhist_rewrap (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
pagerhist_as_text(HistoryBuf *self, PyObject *callback) {
    PagerHistoryBuf *ph = self->pagerhist;
    PyObject *ret = NULL, *t = NULL;
    Py_UCS4 *buf = NULL;
    index_type num;
    if (!ph) Py_RETURN_NONE;

    if (ph->rewrap_needed) pagerhist_rewrap(ph, self->xnum);

#define CALLBACK { \
        if (t == NULL) goto end; \
        ret = PyObject_CallFunctionObjArgs(callback, t, NULL); \
        Py_DECREF(t); \
        if (ret == NULL) goto end; \
        Py_DECREF(ret); \
}

        num = (ph->bufend ? ph->bufend : ph->end) - ph->start;
        buf = ph->buffer + ph->start;
        t = PyUnicode_FromKindAndData(PyUnicode_4BYTE_KIND, buf, num);
        CALLBACK;
        if (ph->bufend) {
            num = ph->end; buf = ph->buffer;
            t = PyUnicode_FromKindAndData(PyUnicode_4BYTE_KIND, buf, num);
            CALLBACK;
        }
        Line l = {.xnum=self->xnum}; get_line(self, 0, &l);
        if (!l.continued) {
            t = PyUnicode_FromString("\n");
            CALLBACK;
        }
#undef CALLBACK
end:
    if (PyErr_Occurred()) return NULL;
    Py_RETURN_NONE;
}