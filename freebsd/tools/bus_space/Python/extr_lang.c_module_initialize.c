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
 int /*<<< orphan*/  PyModule_AddObject (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,int) ; 

__attribute__((used)) static PyObject *
module_initialize(PyObject *bus, PyObject *busdma)
{

	if (bus == NULL || busdma == NULL)
		return (NULL);

	PyModule_AddObject(busdma, "MD_BUS_SPACE", Py_BuildValue("i", 0));
	PyModule_AddObject(busdma, "MD_PHYS_SPACE", Py_BuildValue("i", 1));
	PyModule_AddObject(busdma, "MD_VIRT_SPACE", Py_BuildValue("i", 2));

	PyModule_AddObject(busdma, "SYNC_PREREAD", Py_BuildValue("i", 1));
	PyModule_AddObject(busdma, "SYNC_POSTREAD", Py_BuildValue("i", 2));
	PyModule_AddObject(busdma, "SYNC_PREWRITE", Py_BuildValue("i", 4));
	PyModule_AddObject(busdma, "SYNC_POSTWRITE", Py_BuildValue("i", 8));

	PyModule_AddObject(bus, "dma", busdma);
	return (bus);
}