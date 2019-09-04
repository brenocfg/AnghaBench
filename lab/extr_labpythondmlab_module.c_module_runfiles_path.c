#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  runfiles_path; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * Py_BuildValue (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* get_module_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject* module_runfiles_path(PyObject* self, PyObject* no_arg) {
  return Py_BuildValue("s", get_module_state(self)->runfiles_path);
}