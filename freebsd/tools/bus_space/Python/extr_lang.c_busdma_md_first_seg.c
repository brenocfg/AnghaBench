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
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int*,int*) ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,int) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int bd_md_first_seg (int,int) ; 

__attribute__((used)) static PyObject *
busdma_md_first_seg(PyObject *self, PyObject *args)
{
	int error, mdid, sid, what;

	if (!PyArg_ParseTuple(args, "ii", &mdid, &what))
		return (NULL);
	sid = bd_md_first_seg(mdid, what);
	if (sid == -1)
		Py_RETURN_NONE;
	return (Py_BuildValue("i", sid));
}