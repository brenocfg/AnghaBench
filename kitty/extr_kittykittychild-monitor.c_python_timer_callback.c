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
typedef  unsigned long long id_type ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_Print () ; 
 int /*<<< orphan*/ * PyObject_CallFunction (int /*<<< orphan*/ *,char*,unsigned long long) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
python_timer_callback(id_type timer_id, void *data) {
    PyObject *callback = (PyObject*)data;
    unsigned long long id = timer_id;
    PyObject *ret = PyObject_CallFunction(callback, "K", id);
    if (ret == NULL) PyErr_Print();
    else Py_DECREF(ret);
}