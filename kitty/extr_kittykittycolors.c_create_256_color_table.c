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
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * FG_BG_256 ; 
 int /*<<< orphan*/ * PyErr_NoMemory () ; 
 int /*<<< orphan*/ * PyLong_FromUnsignedLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyTuple_New (size_t) ; 
 int /*<<< orphan*/  PyTuple_SET_ITEM (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_CLEAR (int /*<<< orphan*/ *) ; 
 size_t arraysz (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_FG_BG_table () ; 

PyObject* create_256_color_table() {
    init_FG_BG_table();
    PyObject *ans = PyTuple_New(arraysz(FG_BG_256));
    if (ans == NULL) return PyErr_NoMemory();
    for (size_t i=0; i < arraysz(FG_BG_256); i++) {
        PyObject *temp = PyLong_FromUnsignedLong(FG_BG_256[i]);
        if (temp == NULL) { Py_CLEAR(ans); return NULL; }
        PyTuple_SET_ITEM(ans, i, temp);
    }
    return ans;
}