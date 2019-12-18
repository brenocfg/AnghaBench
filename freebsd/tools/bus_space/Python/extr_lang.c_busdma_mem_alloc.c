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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_IOError ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,int) ; 
 int bd_mem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
busdma_mem_alloc(PyObject *self, PyObject *args)
{
	u_int flags;
	int mdid, tid;

	if (!PyArg_ParseTuple(args, "iI", &tid, &flags))
		return (NULL);
	mdid = bd_mem_alloc(tid, flags);
	if (mdid == -1) {
		PyErr_SetString(PyExc_IOError, strerror(errno));
		return (NULL);
	}
	return (Py_BuildValue("i", mdid));
}