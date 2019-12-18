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
struct TYPE_6__ {scalar_t__ bytes; scalar_t__ doubles; int /*<<< orphan*/  string; } ;
struct TYPE_5__ {scalar_t__ type; long* shape; int dims; } ;
struct TYPE_7__ {TYPE_2__ payload; TYPE_1__ spec; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  TYPE_3__ EnvCApi_Observation ;

/* Variables and functions */
 scalar_t__ EnvCApi_ObservationDoubles ; 
 scalar_t__ EnvCApi_ObservationString ; 
 int ObservationType2typenum (scalar_t__) ; 
 int /*<<< orphan*/  PyArray_BYTES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_NBYTES (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_SimpleNew (int,long*,int) ; 
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_RuntimeError ; 
 int /*<<< orphan*/  PyString_FromStringAndSize (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/ * PyUnicode_FromStringAndSize (int /*<<< orphan*/ ) ; 
 long* calloc (int,int) ; 
 int /*<<< orphan*/  free (long*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject* make_observation(const EnvCApi_Observation* observation) {
  if (observation->spec.type == EnvCApi_ObservationString) {
    PyObject* result =
#if PY_MAJOR_VERSION >= 3
        PyUnicode_FromStringAndSize(
#else  // PY_MAJOR_VERSION >= 3
        PyString_FromStringAndSize(
#endif  // PY_MAJOR_VERSION >= 3
            observation->payload.string, observation->spec.shape[0]);

    if (result == NULL) PyErr_NoMemory();
    return result;
  }

  int observation_type = ObservationType2typenum(observation->spec.type);
  if (observation_type == -1) {
    PyErr_SetString(PyExc_RuntimeError, "Invalid observation spec.");
    return NULL;
  }

  long* bounds = calloc(observation->spec.dims, sizeof(long));
  if (bounds == NULL) {
    PyErr_NoMemory();
    return NULL;
  }

  for (int j = 0; j < observation->spec.dims; ++j) {
    bounds[j] = observation->spec.shape[j];
  }

  PyArrayObject* array = (PyArrayObject*)PyArray_SimpleNew(
      observation->spec.dims, bounds, observation_type);
  free(bounds);

  if (array == NULL) {
    PyErr_NoMemory();
    return NULL;
  }

  const void* src_mem = observation->spec.type == EnvCApi_ObservationDoubles
                            ? (void*)observation->payload.doubles
                            : (void*)observation->payload.bytes;
  memcpy(PyArray_BYTES(array), src_mem, PyArray_NBYTES(array));
  return (PyObject*)array;
}