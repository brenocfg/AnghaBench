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
 int bd_md_destroy (int) ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static PyObject *
busdma_md_destroy(PyObject *self, PyObject *args)
{
	int error, mdid;

	if (!PyArg_ParseTuple(args, "i", &mdid))
		return (NULL);
	error = bd_md_destroy(mdid);
	if (error) {
		PyErr_SetString(PyExc_IOError, strerror(error));
		return (NULL);
	}
	Py_RETURN_NONE;
}