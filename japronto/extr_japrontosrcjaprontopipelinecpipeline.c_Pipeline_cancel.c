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
struct TYPE_3__ {int queue_start; int queue_end; int /*<<< orphan*/ * queue; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PipelineEntry ;
typedef  TYPE_1__ Pipeline ;

/* Variables and functions */
 int /*<<< orphan*/ * PipelineEntry_get_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PipelineEntry_is_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyObject_CallFunctionObjArgs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyObject_GetAttrString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 

void*
Pipeline_cancel(Pipeline* self)
{
  void* result = self;

  PipelineEntry *queue_entry;
  for(queue_entry = self->queue + self->queue_start;
      queue_entry < self->queue + self->queue_end; queue_entry++) {
    if(!PipelineEntry_is_task(*queue_entry))
      continue;

    PyObject* task = PipelineEntry_get_task(*queue_entry);
    PyObject* cancel = NULL;

    if(!(cancel = PyObject_GetAttrString(task, "cancel")))
      goto loop_error;

    PyObject* tmp;
    if(!(tmp = PyObject_CallFunctionObjArgs(cancel, NULL)))
      goto loop_error;
    Py_DECREF(tmp);

    goto loop_finally;

    loop_error:
    result = NULL;

    loop_finally:
    Py_XDECREF(cancel);

    if(!result)
      break;
  }

  return result;
}