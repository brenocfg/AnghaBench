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
typedef  int /*<<< orphan*/  PyMODINIT_FUNC ;

/* Variables and functions */
 int /*<<< orphan*/ * Py_InitModule3 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_docstr ; 
 int /*<<< orphan*/  bus_methods ; 
 int /*<<< orphan*/  busdma_docstr ; 
 int /*<<< orphan*/  busdma_methods ; 
 int /*<<< orphan*/  module_initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

PyMODINIT_FUNC
initbus(void)
{
	PyObject *bus, *busdma;

	bus = Py_InitModule3("bus", bus_methods, bus_docstr);
	busdma = Py_InitModule3("busdma", busdma_methods, busdma_docstr);
	(void)module_initialize(bus, busdma);
}