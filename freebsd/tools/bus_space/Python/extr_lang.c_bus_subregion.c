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
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int*,long*,long*) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_IOError ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,int) ; 
 int bs_subregion (int,long,long) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
bus_subregion(PyObject *self, PyObject *args)
{
	long ofs, sz;
	int rid0, rid;

	if (!PyArg_ParseTuple(args, "ill", &rid0, &ofs, &sz))
		return (NULL);
	rid = bs_subregion(rid0, ofs, sz);
	if (rid == -1) {
		PyErr_SetString(PyExc_IOError, strerror(errno));
		return (NULL);
	}
	return (Py_BuildValue("i", rid));
}