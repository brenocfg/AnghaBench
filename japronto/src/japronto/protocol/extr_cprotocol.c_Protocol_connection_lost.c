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
struct TYPE_3__ {int closed; scalar_t__ none_cnt; scalar_t__ true_cnt; scalar_t__ false_cnt; int /*<<< orphan*/  pipeline; int /*<<< orphan*/  app; int /*<<< orphan*/  parser; int /*<<< orphan*/  feed_disconnect; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ Protocol ;

/* Variables and functions */
 int /*<<< orphan*/  Parser_feed_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Pipeline_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyObject_CallFunctionObjArgs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyObject_GetAttrString (int /*<<< orphan*/ ,char*) ; 
 int PySet_Discard (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_False ; 
 int /*<<< orphan*/ * Py_None ; 
 scalar_t__ Py_REFCNT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_True ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XINCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  printf (char*,size_t,size_t,size_t) ; 

__attribute__((used)) static PyObject*
Protocol_connection_lost(Protocol* self, PyObject* args)
{
  self->closed = true;

  PyObject* connections = NULL;
  PyObject* result = Py_None;
#ifdef PARSER_STANDALONE
  PyObject* result = PyObject_CallFunctionObjArgs(
    self->feed_disconnect, NULL);
  if(!result)
    goto error;
  Py_DECREF(result); // FIXME: result can leak
#else
  if(!Parser_feed_disconnect(&self->parser))
    goto error;
#endif

  if(!(connections = PyObject_GetAttrString(self->app, "_connections")))
    goto error;

  if(PySet_Discard(connections, (PyObject*)self) == -1)
    goto error;

  if(!Pipeline_cancel(&self->pipeline))
    goto error;

#ifdef PROTOCOL_TRACK_REFCNT
printf("lost: %ld, %ld, %ld\n",
  (size_t)Py_REFCNT(Py_None), (size_t)Py_REFCNT(Py_True), (size_t)Py_REFCNT(Py_False));
  assert(Py_REFCNT(Py_None) == self->none_cnt);
  assert(Py_REFCNT(Py_True) == self->true_cnt);
  assert(Py_REFCNT(Py_False) >= self->false_cnt);
#endif

  goto finally;

  error:
  result = NULL;

  finally:
  Py_XDECREF(connections);
  Py_XINCREF(result);
  return result;
}