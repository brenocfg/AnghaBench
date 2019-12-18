#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int id; int observation_count; int /*<<< orphan*/ * observations; } ;
struct TYPE_6__ {int status; int /*<<< orphan*/  context; TYPE_1__* env_c_api; } ;
struct TYPE_5__ {int (* event_type_count ) (int /*<<< orphan*/ ) ;int (* event_count ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* event_type_name ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* event ) (int /*<<< orphan*/ ,int,TYPE_3__*) ;} ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ LabObject ;
typedef  TYPE_3__ EnvCApi_Event ;

/* Variables and functions */
#define  ENV_STATUS_INITIALIZED 130 
#define  EnvCApi_EnvironmentStatus_Running 129 
#define  EnvCApi_EnvironmentStatus_Terminated 128 
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_RuntimeError ; 
 int /*<<< orphan*/ * PyList_New (int) ; 
 int /*<<< orphan*/  PyList_SetItem (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyString_FromString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyTuple_New (int) ; 
 int /*<<< orphan*/  PyTuple_SetItem (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyUnicode_FromString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_observation (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static PyObject* Lab_events(PyObject* pself, PyObject* no_arg) {
  LabObject* self = (LabObject*)pself;

  switch (self->status) {
    case ENV_STATUS_INITIALIZED:
    case EnvCApi_EnvironmentStatus_Running:
    case EnvCApi_EnvironmentStatus_Terminated:
      break;
    default:
      PyErr_SetString(PyExc_RuntimeError,
                      "Environment in wrong status for call to events()");
      return NULL;
  }

  int event_type_count = self->env_c_api->event_type_count(self->context);
  int event_count = self->env_c_api->event_count(self->context);
  PyObject* result = PyList_New(event_count);
  if (result == NULL) {
    PyErr_NoMemory();
    return NULL;
  }

  for (int event_id = 0; event_id < event_count; ++event_id) {
    EnvCApi_Event event;
    self->env_c_api->event(self->context, event_id, &event);
    if (0 > event.id || event.id >= event_type_count) {
      PyErr_Format(PyExc_RuntimeError,
                   "Environment generated invalid event id. "
                   "Event id(%d) must be in range [0, %d).",
                   event.id, event_type_count);
      Py_DECREF(result);
      return NULL;
    }
    PyObject* entry = PyTuple_New(2);
    PyTuple_SetItem(entry, 0,
#if PY_MAJOR_VERSION >= 3
                    PyUnicode_FromString(
#else  // PY_MAJOR_VERSION >= 3
                    PyString_FromString(
#endif  // PY_MAJOR_VERSION >= 3
                        self->env_c_api->event_type_name(self->context,
                                                         event.id)));

    PyObject* observation_list = PyList_New(event.observation_count);
    if (observation_list == NULL) {
      Py_DECREF(result);
      return NULL;
    }
    for (int obs_id = 0; obs_id < event.observation_count; ++obs_id) {
      PyObject* obs_entry = make_observation(&event.observations[obs_id]);
      if (obs_entry == NULL) {
        Py_DECREF(observation_list);
        Py_DECREF(result);
        return NULL;
      }
      PyList_SetItem(observation_list, obs_id, obs_entry);
    }
    PyTuple_SetItem(entry, 1, observation_list);
    PyList_SetItem(result, event_id, entry);
  }

  return result;
}