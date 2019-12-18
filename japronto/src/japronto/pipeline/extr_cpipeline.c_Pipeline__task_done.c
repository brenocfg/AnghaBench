#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int queue_start; int queue_end; int /*<<< orphan*/ * protocol; int /*<<< orphan*/ * queue; int /*<<< orphan*/  (* ready ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PipelineEntry ;
typedef  TYPE_1__ Pipeline ;

/* Variables and functions */
 scalar_t__ PIPELINE_EMPTY (TYPE_1__*) ; 
 int /*<<< orphan*/  PipelineEntry_DECREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PipelineEntry_get_task (int /*<<< orphan*/ ) ; 
 scalar_t__ PipelineEntry_is_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyObject_CallFunctionObjArgs (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ *),int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * PyObject_GetAttrString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_False ; 
 int /*<<< orphan*/ * Py_True ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XINCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject*
Pipeline__task_done(Pipeline* self, PyObject* task)
{
  PyObject* result = Py_True;

  PipelineEntry *queue_entry;
  for(queue_entry = self->queue + self->queue_start;
      queue_entry < self->queue + self->queue_end; queue_entry++) {
    PyObject* done = NULL;
    PyObject* done_result = NULL;
    result = Py_True;

    if(PipelineEntry_is_task(*queue_entry)) {
      task = PipelineEntry_get_task(*queue_entry);

      if(!(done = PyObject_GetAttrString(task, "done")))
        goto loop_error;

      if(!(done_result = PyObject_CallFunctionObjArgs(done, NULL)))
        goto loop_error;

      if(done_result == Py_False) {
        result = Py_False;
        goto loop_finally;
      }
    }

#ifdef PIPELINE_OPAQUE
    PyObject* tmp;
    if(!(tmp = PyObject_CallFunctionObjArgs(self->ready, *queue_entry, NULL)))
      goto loop_error;
    Py_DECREF(tmp);
#else
    if(!self->ready(*queue_entry, self->protocol))
      goto loop_error;
#endif

    PipelineEntry_DECREF(*queue_entry);

    goto loop_finally;

    loop_error:
    result = NULL;

    loop_finally:
    Py_XDECREF(done_result);
    Py_XDECREF(done);
    if(!result)
      goto error;
    if(result == Py_False)
      break;
  }

  self->queue_start = queue_entry - self->queue;

#ifndef PIPELINE_OPAQUE
  if(PIPELINE_EMPTY(self))
    // we became empty so release protocol
    Py_DECREF(self->protocol);
#endif

  goto finally;

  error:
  result = NULL;

  finally:
  Py_XINCREF(result);
  return result;
}