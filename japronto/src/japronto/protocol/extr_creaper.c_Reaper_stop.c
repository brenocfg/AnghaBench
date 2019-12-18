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
struct TYPE_3__ {int /*<<< orphan*/  check_idle_handle; } ;
typedef  TYPE_1__ Reaper ;
typedef  void PyObject ;

/* Variables and functions */
 void* PyObject_CallFunctionObjArgs (void*,int /*<<< orphan*/ *) ; 
 void* PyObject_GetAttrString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Py_DECREF (void*) ; 
 void* Py_None ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  Py_XDECREF (void*) ; 
 int /*<<< orphan*/  Py_XINCREF (void*) ; 

__attribute__((used)) static PyObject*
Reaper_stop(Reaper* self)
{
#ifdef REAPER_ENABLED
  void* result = Py_None;
  PyObject* cancel = NULL;

  if(!(cancel = PyObject_GetAttrString(self->check_idle_handle, "cancel")))
    goto error;

  PyObject* tmp;
  if(!(tmp = PyObject_CallFunctionObjArgs(cancel, NULL)))
    goto error;
  Py_DECREF(tmp);

  goto finally;

  error:
  result = NULL;

  finally:
  Py_XINCREF(result);
  Py_XDECREF(cancel);
  return result;
#else
  Py_RETURN_NONE;
#endif
}