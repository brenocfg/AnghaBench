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
 int /*<<< orphan*/  DEEPMIND_LAB_WRAPPER_VERSION ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject* module_version(PyObject* self, PyObject* no_arg) {
  return Py_BuildValue("s", DEEPMIND_LAB_WRAPPER_VERSION);
}