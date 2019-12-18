#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  runfiles_path; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ LabModuleState ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,char const**) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_RuntimeError ; 
 int /*<<< orphan*/  Py_RETURN_TRUE ; 
 TYPE_1__* get_module_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static PyObject* module_set_runfiles_path(PyObject* self, PyObject* args) {
  const char* new_path;
  if (!PyArg_ParseTuple(args, "s", &new_path)) {
    return NULL;
  }

  LabModuleState* module_state = get_module_state(self);
  if (strlen(new_path) < sizeof(module_state->runfiles_path)) {
    strcpy(module_state->runfiles_path, new_path);
  } else {
    PyErr_SetString(PyExc_RuntimeError, "Runfiles directory name too long!");
    return NULL;
  }

  Py_RETURN_TRUE;
}