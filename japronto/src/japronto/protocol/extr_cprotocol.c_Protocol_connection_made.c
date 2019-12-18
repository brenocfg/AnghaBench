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
struct TYPE_3__ {int closed; scalar_t__ last_read_ops; scalar_t__ read_ops; scalar_t__ idle_time; int /*<<< orphan*/ * app; void* writelines; void* write; int /*<<< orphan*/ * transport; void* false_cnt; void* true_cnt; void* none_cnt; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ Protocol ;

/* Variables and functions */
 void* PyObject_GetAttrString (int /*<<< orphan*/ *,char*) ; 
 int PySet_Add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_False ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_None ; 
 void* Py_REFCNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  Py_True ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,size_t,size_t,size_t) ; 

__attribute__((used)) static PyObject*
Protocol_connection_made(Protocol* self, PyObject* transport)
{
#ifdef PROTOCOL_TRACK_REFCNT
  printf("made: %ld, %ld, %ld, ",
    (size_t)Py_REFCNT(Py_None), (size_t)Py_REFCNT(Py_True), (size_t)Py_REFCNT(Py_False));
  self->none_cnt = Py_REFCNT(Py_None);
  self->true_cnt = Py_REFCNT(Py_True);
  self->false_cnt = Py_REFCNT(Py_False);
#endif

  PyObject* connections = NULL;
  self->transport = transport;
  Py_INCREF(self->transport);

  if(!(self->write = PyObject_GetAttrString(transport, "write")))
    goto error;

  if(!(self->writelines = PyObject_GetAttrString(transport, "writelines")))
    goto error;

  if(!(connections = PyObject_GetAttrString(self->app, "_connections")))
    goto error;

#ifdef REAPER_ENABLED
  self->idle_time = 0;
  self->read_ops = 0;
  self->last_read_ops = 0;
#endif

  if(PySet_Add(connections, (PyObject*)self) == -1)
    goto error;

  self->closed = false;

  goto finally;

  error:
  return NULL;

  finally:
  Py_XDECREF(connections);
  Py_RETURN_NONE;
}