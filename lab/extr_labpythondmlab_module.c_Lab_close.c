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
typedef  int /*<<< orphan*/  LabObject ;

/* Variables and functions */
 int /*<<< orphan*/  Py_RETURN_FALSE ; 
 int /*<<< orphan*/  Py_RETURN_TRUE ; 
 scalar_t__ env_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject* Lab_close(PyObject* self, PyObject* no_arg) {
  if (env_close((LabObject*)self)) {
    Py_RETURN_TRUE;
  } else {
    Py_RETURN_FALSE;
  }
}