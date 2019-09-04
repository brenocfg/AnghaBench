#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  len; } ;
struct TYPE_6__ {int /*<<< orphan*/  write; TYPE_2__ gather; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ Protocol ;
typedef  TYPE_2__ Gather ;

/* Variables and functions */
 int /*<<< orphan*/ * Gather_flush (TYPE_2__*) ; 
 int /*<<< orphan*/ * PyObject_CallFunctionObjArgs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 

Protocol*
Protocol_on_incomplete(Protocol* self)
{
  Gather* gather = &self->gather;
  PyObject* gather_buffer = NULL;

  if(!gather->len)
    goto finally;

  if(!(gather_buffer = Gather_flush(gather)))
    goto error;

  PyObject* tmp;
  if(!(tmp = PyObject_CallFunctionObjArgs(self->write, gather_buffer, NULL)))
    goto error;
  Py_DECREF(tmp);

  goto finally;

  error:
  self = NULL;

  finally:
  Py_XDECREF(gather_buffer);
  return self;
}