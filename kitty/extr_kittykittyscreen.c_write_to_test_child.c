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
struct TYPE_3__ {int /*<<< orphan*/  test_child; } ;
typedef  TYPE_1__ Screen ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_Print () ; 
 int /*<<< orphan*/ * PyObject_CallMethod (int /*<<< orphan*/ ,char*,char*,char const*,size_t) ; 
 int /*<<< orphan*/  Py_CLEAR (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
write_to_test_child(Screen *self, const char *data, size_t sz) {
    PyObject *r = PyObject_CallMethod(self->test_child, "write", "y#", data, sz); if (r == NULL) PyErr_Print(); Py_CLEAR(r);
}