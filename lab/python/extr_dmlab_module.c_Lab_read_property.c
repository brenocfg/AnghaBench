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
struct TYPE_3__ {int (* read_property ) (int /*<<< orphan*/ ,char*,char const**) ;} ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ LabObject ;

/* Variables and functions */
#define  EnvCApi_PropertyResult_InvalidArgument 131 
#define  EnvCApi_PropertyResult_NotFound 130 
#define  EnvCApi_PropertyResult_PermissionDenied 129 
#define  EnvCApi_PropertyResult_Success 128 
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,char**) ; 
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  PyExc_KeyError ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/ * PyString_FromString (char const*) ; 
 int /*<<< orphan*/ * PyUnicode_FromString (char const*) ; 
 int stub1 (int /*<<< orphan*/ ,char*,char const**) ; 

__attribute__((used)) static PyObject* Lab_read_property(PyObject* pself, PyObject* args,
                                   PyObject* kwds) {
  LabObject* self = (LabObject*)pself;
  char* key = NULL;
  const char* value = NULL;
  char* kwlist[] = {"key", NULL};

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "s", kwlist, &key)) {
    return NULL;
  }

  switch (self->env_c_api->read_property(self->context, key, &value)) {
    case EnvCApi_PropertyResult_Success:
#if PY_MAJOR_VERSION >= 3
      return PyUnicode_FromString(value);
#else
      return PyString_FromString(value);
#endif  // PY_MAJOR_VERSION >= 3
    case EnvCApi_PropertyResult_PermissionDenied:
      PyErr_Format(PyExc_TypeError, "'%s' not readable.", key);
      break;
    case EnvCApi_PropertyResult_InvalidArgument:
      PyErr_Format(PyExc_TypeError, "Internal error while reading key '%s'.",
                   key);
      break;
    case EnvCApi_PropertyResult_NotFound:
    default:
      PyErr_Format(PyExc_KeyError, "'%s' not found.", key);
      break;
  }
  return NULL;
}