#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Screen ;
typedef  scalar_t__ Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyErr_NoMemory () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  PyUnicode_Check (int /*<<< orphan*/ *) ; 
 void* PyUnicode_DATA (int /*<<< orphan*/ *) ; 
 scalar_t__ PyUnicode_GET_LENGTH (int /*<<< orphan*/ *) ; 
 int PyUnicode_KIND (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyUnicode_READ (int,void*,scalar_t__) ; 
 scalar_t__ PyUnicode_READY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  screen_draw (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject*
draw(Screen *self, PyObject *src) {
    if (!PyUnicode_Check(src)) { PyErr_SetString(PyExc_TypeError, "A unicode string is required"); return NULL; }
    if (PyUnicode_READY(src) != 0) { return PyErr_NoMemory(); }
    int kind = PyUnicode_KIND(src);
    void *buf = PyUnicode_DATA(src);
    Py_ssize_t sz = PyUnicode_GET_LENGTH(src);
    for (Py_ssize_t i = 0; i < sz; i++) screen_draw(self, PyUnicode_READ(kind, buf, i));
    Py_RETURN_NONE;
}