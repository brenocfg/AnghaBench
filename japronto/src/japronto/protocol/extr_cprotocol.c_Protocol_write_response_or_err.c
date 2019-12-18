#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ ResponseType; int /*<<< orphan*/ * (* Response_render ) (TYPE_1__*,int) ;} ;
struct TYPE_16__ {size_t responses_end; scalar_t__ len; int /*<<< orphan*/ ** responses; int /*<<< orphan*/  enabled; } ;
struct TYPE_15__ {int /*<<< orphan*/ * request_logger; int /*<<< orphan*/ * write; TYPE_4__ gather; int /*<<< orphan*/  error_handler; } ;
struct TYPE_14__ {int simple; int /*<<< orphan*/ * done_callbacks; int /*<<< orphan*/  exception; } ;
struct TYPE_13__ {scalar_t__ keep_alive; } ;
typedef  TYPE_1__ Response ;
typedef  TYPE_2__ Request ;
typedef  scalar_t__ Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_3__ Protocol ;
typedef  TYPE_4__ Gather ;

/* Variables and functions */
 scalar_t__ GATHER_MAX_LEN ; 
 size_t GATHER_MAX_RESP ; 
 int /*<<< orphan*/ * Gather_flush (TYPE_4__*) ; 
 scalar_t__ KEEP_ALIVE_FALSE ; 
 int /*<<< orphan*/  Protocol_catch_exception (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Protocol_close (TYPE_3__*) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/ * PyList_GET_ITEM (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ PyList_GET_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyObject_CallFunctionObjArgs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 scalar_t__ Py_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ Py_TYPE (TYPE_1__*) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 TYPE_6__* response_capi ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__*,int) ; 

__attribute__((used)) static inline Protocol*
Protocol_write_response_or_err(Protocol* self, PyObject* request, Response* response)
{
    Protocol* result = self;
    PyObject* response_bytes = NULL;
    PyObject* error_result = NULL;
    PyObject* gather_buffer = NULL;

    if(response && Py_TYPE(response) != response_capi->ResponseType)
    {
      PyErr_SetString(PyExc_ValueError, "View did not return Response instance");
      Protocol_catch_exception(request);
      response = NULL;
    }

    if(!response) {
      error_result = PyObject_CallFunctionObjArgs(
        self->error_handler, request, ((Request*)request)->exception, NULL);
      if(!error_result)
        goto error;

      ((Request*)request)->simple = false;
      if(!Protocol_write_response_or_err(self, request, (Response*)error_result))
        goto error;

      goto finally;
    }

    if(!(response_bytes =
         response_capi->Response_render(response, ((Request*)request)->simple)))
      goto error;

    PyObject* tmp;

    PyObject* done_callbacks = ((Request*)request)->done_callbacks;
    for(Py_ssize_t i = 0; done_callbacks && i < PyList_GET_SIZE(done_callbacks); i++) {
      PyObject* callback = PyList_GET_ITEM(done_callbacks, i);

      if(!(tmp = PyObject_CallFunctionObjArgs(callback, request, NULL)))
        goto error;
      Py_DECREF(tmp);
    }

    Gather* gather = &self->gather;

    if(!gather->enabled)
      goto maybe_flush;

    if(gather->responses_end == GATHER_MAX_RESP)
      goto maybe_flush;

    if(gather->len + Py_SIZE(response_bytes) > GATHER_MAX_LEN)
      goto maybe_flush;

    gather->responses[gather->responses_end] = response_bytes;
    gather->responses_end++;
    gather->len += Py_SIZE(response_bytes);
    response_bytes = NULL;

    goto dont_flush;

    maybe_flush:
    if(!gather->len)
      goto dont_flush;

    if(!(gather_buffer = Gather_flush(gather)))
      goto error;

    if(!(tmp = PyObject_CallFunctionObjArgs(self->write, gather_buffer, NULL)))
      goto error;
    Py_DECREF(tmp);

    dont_flush:

    if(response_bytes) {
      if(!(tmp = PyObject_CallFunctionObjArgs(self->write, response_bytes, NULL)))
        goto error;
      Py_DECREF(tmp);
    }

    if(self->request_logger) {
      if(!(tmp = PyObject_CallFunctionObjArgs(self->request_logger, request, NULL)))
        goto error;
      Py_DECREF(tmp);
    }

    if(response->keep_alive == KEEP_ALIVE_FALSE) {
      if(!Protocol_close(self))
        goto error;
    }

    goto finally;

    error:
    result = NULL;

    finally:
    Py_XDECREF(gather_buffer);
    Py_XDECREF(error_result);
    Py_XDECREF(response_bytes);
    return result;
}