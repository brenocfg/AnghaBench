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
struct TYPE_3__ {int /*<<< orphan*/  transport; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ Protocol ;

/* Variables and functions */
 int /*<<< orphan*/ * PyObject_CallFunctionObjArgs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyObject_GetAttrString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void*
Protocol_close(Protocol* self)
{
  void* result = self;

  PyObject* close = NULL;
  close = PyObject_GetAttrString(self->transport, "close");
  if(!close)
    goto error;
  PyObject* tmp = PyObject_CallFunctionObjArgs(close, NULL);
  if(!tmp)
    goto error;
  Py_DECREF(tmp);

  goto finally;

  error:
  result = NULL;

  finally:
  Py_XDECREF(close);
  return result;
}