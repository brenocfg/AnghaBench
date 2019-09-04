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
typedef  int /*<<< orphan*/  Line ;

/* Variables and functions */
 int /*<<< orphan*/ * PyObject_Repr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_CLEAR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * line_as_unicode (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject*
__repr__(Line* self) {
    PyObject *s = line_as_unicode(self);
    if (s == NULL) return NULL;
    PyObject *ans = PyObject_Repr(s);
    Py_CLEAR(s);
    return ans;
}