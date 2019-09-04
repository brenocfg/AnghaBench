#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  context; TYPE_1__* env_c_api; } ;
struct TYPE_3__ {int (* action_discrete_count ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* action_discrete_name ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* action_discrete_bounds ) (int /*<<< orphan*/ ,int,int*,int*) ;} ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ LabObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_RuntimeError ; 
 int /*<<< orphan*/ * PyList_New (int) ; 
 scalar_t__ PyList_SetItem (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_BuildValue (char*,char*,int,char*,int,char*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,int*,int*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static PyObject* Lab_action_spec(PyObject* pself, PyObject* no_arg) {
  LabObject* self = (LabObject*)pself;
  PyObject* discrete;

  int count = self->env_c_api->action_discrete_count(self->context);
  discrete = PyList_New(count);
  if (discrete == NULL) {
    PyErr_NoMemory();
    return NULL;
  }
  int min_discrete, max_discrete;
  for (int i = 0; i < count; ++i) {
    self->env_c_api->action_discrete_bounds(self->context, i, &min_discrete,
                                            &max_discrete);
    if (PyList_SetItem(discrete, i,
                       Py_BuildValue("{s:i,s:i,s:s}", "min", min_discrete,
                                     "max", max_discrete, "name",
                                     self->env_c_api->action_discrete_name(
                                         self->context, i))) != 0) {
      PyErr_SetString(PyExc_RuntimeError, "Unable to populate list");
      return NULL;
    }
  }

  return discrete;
}