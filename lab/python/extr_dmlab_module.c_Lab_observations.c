#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int observation_count; int /*<<< orphan*/ * observation_indices; int /*<<< orphan*/  context; TYPE_1__* env_c_api; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* observation_name ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* observation ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ LabObject ;
typedef  int /*<<< orphan*/  EnvCApi_Observation ;

/* Variables and functions */
 int /*<<< orphan*/ * PyDict_New () ; 
 int /*<<< orphan*/  PyDict_SetItemString (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_RuntimeError ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_running (TYPE_2__*) ; 
 int /*<<< orphan*/ * make_observation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject* Lab_observations(PyObject* pself, PyObject* no_arg) {
  LabObject* self = (LabObject*)pself;

  if (!is_running((self))) {
    PyErr_SetString(PyExc_RuntimeError,
                    "Environment in wrong status for call to observations()");
    return NULL;
  }

  PyObject* result = PyDict_New();
  if (result == NULL) {
    PyErr_NoMemory();
    return NULL;
  }

  EnvCApi_Observation observation;

  for (int i = 0; i < self->observation_count; ++i) {
    self->env_c_api->observation(self->context, self->observation_indices[i],
                                 &observation);
    PyObject* entry = make_observation(&observation);
    if (entry == NULL) {
      Py_DECREF(result);
      return NULL;
    }

    // PyDict_SetItemString increments reference count.
    PyDict_SetItemString(result,
                         self->env_c_api->observation_name(
                             self->context, self->observation_indices[i]),
                         entry);
    Py_DECREF(entry);
  }
  return result;
}