#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ typeobj; } ;
struct TYPE_8__ {scalar_t__ type; int dims; int /*<<< orphan*/ * shape; } ;
struct TYPE_7__ {int /*<<< orphan*/  context; TYPE_1__* env_c_api; } ;
struct TYPE_6__ {int (* observation_count ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* observation_name ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* observation_spec ) (int /*<<< orphan*/ ,int,TYPE_3__*) ;} ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ LabObject ;
typedef  TYPE_3__ EnvCApi_ObservationSpec ;

/* Variables and functions */
 scalar_t__ EnvCApi_ObservationString ; 
 int ObservationType2typenum (scalar_t__) ; 
 TYPE_5__* PyArray_DescrFromType (int) ; 
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_RuntimeError ; 
 int /*<<< orphan*/  PyInt_FromLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyList_New (int) ; 
 scalar_t__ PyList_SetItem (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyString_Type ; 
 int /*<<< orphan*/ * PyTuple_New (int) ; 
 scalar_t__ PyTuple_SetItem (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyUnicode_Type ; 
 int /*<<< orphan*/  Py_BuildValue (char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static PyObject* Lab_observation_spec(PyObject* pself, PyObject* no_arg) {
  LabObject* self = (LabObject*)pself;
  int count = self->env_c_api->observation_count(self->context);
  PyObject* result = PyList_New(count);
  if (result == NULL) {
    PyErr_NoMemory();
    return NULL;
  }
  EnvCApi_ObservationSpec spec;
  PyObject* type;
  PyObject* shape;

  for (int idx = 0; idx < count; ++idx) {
    self->env_c_api->observation_spec(self->context, idx, &spec);
    if (spec.type == EnvCApi_ObservationString) {
#if PY_MAJOR_VERSION >= 3
      type = (PyObject*)(&PyUnicode_Type);
#else  //  PY_MAJOR_VERSION >= 3
      type = (PyObject*)(&PyString_Type);
#endif  // PY_MAJOR_VERSION >= 3
      shape = PyTuple_New(0);
      if (PyList_SetItem(result, idx, Py_BuildValue(
              "{s:s,s:N,s:O}",
              "name", self->env_c_api->observation_name(self->context, idx),
              "shape", shape,
              "dtype", type)) != 0) {
        PyErr_SetString(PyExc_RuntimeError, "Unable to populate list");
        return NULL;
      }
      continue;
    }
    int observation_type = ObservationType2typenum(spec.type);
    if (observation_type == -1) {
      PyErr_SetString(PyExc_RuntimeError, "Invalid observation spec.");
      return NULL;
    }

    type = (PyObject*)PyArray_DescrFromType(observation_type)->typeobj;
    shape = PyTuple_New(spec.dims);
    for (int j = 0; j < spec.dims; ++j) {
      if (PyTuple_SetItem(shape, j, PyInt_FromLong(spec.shape[j])) != 0) {
        PyErr_SetString(PyExc_RuntimeError, "Unable to populate tuple");
        return NULL;
      }
    }
    if (PyList_SetItem(result, idx, Py_BuildValue(
            "{s:s,s:N,s:O}",
            "name", self->env_c_api->observation_name(self->context, idx),
            "shape", shape,
            "dtype", type)) != 0) {
      PyErr_SetString(PyExc_RuntimeError, "Unable to populate list");
      return NULL;
    }
  }
  return result;
}