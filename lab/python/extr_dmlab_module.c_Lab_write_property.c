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
struct TYPE_3__ {int (* write_property ) (int /*<<< orphan*/ ,char*,char*) ;} ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ LabObject ;

/* Variables and functions */
#define  EnvCApi_PropertyResult_InvalidArgument 131 
#define  EnvCApi_PropertyResult_NotFound 130 
#define  EnvCApi_PropertyResult_PermissionDenied 129 
#define  EnvCApi_PropertyResult_Success 128 
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,char**,char**) ; 
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  PyExc_KeyError ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int stub1 (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static PyObject* Lab_write_property(PyObject* pself, PyObject* args,
                                    PyObject* kwds) {
  LabObject* self = (LabObject*)pself;
  char* key = NULL;
  char* value = NULL;
  char* kwlist[] = {"key", "value", NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "ss", kwlist, &key, &value)) {
    return NULL;
  }
  switch (self->env_c_api->write_property(self->context, key, value)) {
    case EnvCApi_PropertyResult_Success:
      Py_RETURN_NONE;
    case EnvCApi_PropertyResult_PermissionDenied:
      PyErr_Format(PyExc_TypeError, "'%s' not writable.", key);
      break;
    case EnvCApi_PropertyResult_InvalidArgument:
      PyErr_Format(PyExc_TypeError, "Type error! Cannot assign '%s' to '%s'.",
                   value, key);
      break;
    case EnvCApi_PropertyResult_NotFound:
    default:
      PyErr_Format(PyExc_KeyError, "'%s' not found.", key);
      break;
  }
  return NULL;
}