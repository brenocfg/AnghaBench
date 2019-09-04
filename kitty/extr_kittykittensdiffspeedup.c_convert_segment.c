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
struct TYPE_3__ {int /*<<< orphan*/ * end_code; int /*<<< orphan*/ * start_code; void* start_pos; void* current_pos; void* end_pos; } ;
typedef  TYPE_1__ Segment ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 void* PyLong_AsUnsignedLong (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyObject_GetAttrString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PyUnicode_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
convert_segment(PyObject *highlight, Segment *dest) {
    PyObject *val = NULL;
#define I
#define A(x, d, c) { \
    val = PyObject_GetAttrString(highlight, #x); \
    if (val == NULL) return false; \
    dest->d = c(val); Py_DECREF(val); \
}
    A(start, start_pos, PyLong_AsUnsignedLong);
    A(end, end_pos, PyLong_AsUnsignedLong);
    dest->current_pos = dest->start_pos;
    A(start_code, start_code, I);
    A(end_code, end_code, I);
    if (!PyUnicode_Check(dest->start_code)) { PyErr_SetString(PyExc_TypeError, "start_code is not a string"); return false; }
    if (!PyUnicode_Check(dest->end_code)) { PyErr_SetString(PyExc_TypeError, "end_code is not a string"); return false; }
#undef A
#undef I
    return true;
}