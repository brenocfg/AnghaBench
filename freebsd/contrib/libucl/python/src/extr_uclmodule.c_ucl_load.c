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
 scalar_t__ PyArg_ParseTuple (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/ * _internal_load_ucl (char*) ; 

__attribute__((used)) static PyObject*
ucl_load (PyObject *self, PyObject *args)
{
	char *uclstr;

	if (PyArg_ParseTuple(args, "z", &uclstr)) {
		if (!uclstr) {
			Py_RETURN_NONE;
		}

		return _internal_load_ucl(uclstr);
	}

	return NULL;
}