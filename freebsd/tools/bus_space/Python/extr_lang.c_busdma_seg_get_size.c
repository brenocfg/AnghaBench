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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_IOError ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,int /*<<< orphan*/ ) ; 
 int bd_seg_get_size (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static PyObject *
busdma_seg_get_size(PyObject *self, PyObject *args)
{
	u_long size;
	int error, sid;

	if (!PyArg_ParseTuple(args, "i", &sid))
		return (NULL);
	error = bd_seg_get_size(sid, &size);
	if (error) {
		PyErr_SetString(PyExc_IOError, strerror(error));
		return (NULL);
	}
	return (Py_BuildValue("k", size));
}