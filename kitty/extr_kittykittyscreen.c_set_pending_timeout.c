#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  wait_time; } ;
struct TYPE_5__ {TYPE_1__ pending_mode; } ;
typedef  TYPE_2__ Screen ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  PyFloat_AS_DOUBLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyFloat_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyFloat_FromDouble (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject*
set_pending_timeout(Screen *self, PyObject *val) {
    if (!PyFloat_Check(val)) { PyErr_SetString(PyExc_TypeError, "timeout must be a float"); return NULL; }
    PyObject *ans = PyFloat_FromDouble(self->pending_mode.wait_time);
    self->pending_mode.wait_time = PyFloat_AS_DOUBLE(val);
    return ans;
}