#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * write; int /*<<< orphan*/  app; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ Protocol ;

/* Variables and functions */
 int /*<<< orphan*/  Protocol_close (TYPE_1__*) ; 
 int /*<<< orphan*/ * PyObject_CallFunctionObjArgs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyObject_GetAttrString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 

Protocol*
Protocol_on_error(Protocol* self, PyObject* error)
{
  PyObject* protocol_error_handler = NULL;
  PyObject* response = NULL;

  if(!(protocol_error_handler =
       PyObject_GetAttrString(self->app, "protocol_error_handler")))
    goto error;

  if(!(response =
       PyObject_CallFunctionObjArgs(protocol_error_handler, error, NULL)))
    goto error;

  PyObject* tmp;
  if(!(tmp = PyObject_CallFunctionObjArgs(self->write, response, NULL)))
    goto error;
  Py_DECREF(tmp);

  if(!Protocol_close(self))
    goto error;

  goto finally;

  error:
  self = NULL;

  finally:
  Py_XDECREF(response);
  Py_XDECREF(protocol_error_handler);
  return self;
}