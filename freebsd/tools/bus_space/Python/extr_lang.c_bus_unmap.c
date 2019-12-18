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
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_IOError ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  bs_unmap (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
bus_unmap(PyObject *self, PyObject *args)
{
	int rid;

	if (!PyArg_ParseTuple(args, "i", &rid))
		return (NULL);
	if (!bs_unmap(rid)) {
		PyErr_SetString(PyExc_IOError, strerror(errno));
		return (NULL);
	}
	Py_RETURN_NONE;
}