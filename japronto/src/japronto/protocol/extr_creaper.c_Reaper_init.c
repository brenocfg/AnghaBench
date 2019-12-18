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
struct TYPE_4__ {void* check_idle; void* connections; void* call_later; int /*<<< orphan*/  idle_timeout; int /*<<< orphan*/ * check_interval; } ;
typedef  TYPE_1__ Reaper ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_IDLE_TIMEOUT ; 
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PyLong_AsLong (int /*<<< orphan*/ *) ; 
 void* PyObject_GetAttrString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Reaper_schedule_check_idle (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debug_print (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * default_check_interval ; 

__attribute__((used)) static int
Reaper_init(Reaper* self, PyObject* args, PyObject* kwds)
{
  PyObject* loop = NULL;
  int result = 0;

  PyObject* app = NULL;
  PyObject* idle_timeout = NULL;

  static char* kwlist[] = {"app", "check_interval", "idle_timeout", NULL};

  if (!PyArg_ParseTupleAndKeywords(
      args, kwds, "|OOO", kwlist, &app, &self->check_interval, &idle_timeout))
      goto error;

  assert(app);

  if(!self->check_interval)
    self->check_interval = default_check_interval;
  Py_INCREF(self->check_interval);

  assert(PyLong_AsLong(self->check_interval) >= 0);

  if(!idle_timeout)
    self->idle_timeout = DEFAULT_IDLE_TIMEOUT;
  else
    self->idle_timeout = PyLong_AsLong(idle_timeout);

  assert(self->idle_timeout >= 0);

  debug_print("check_interval %ld", PyLong_AsLong(self->check_interval));
  debug_print("idle_timeout %ld", self->idle_timeout);

  if(!(loop = PyObject_GetAttrString(app, "_loop")))
    goto error;

  if(!(self->call_later = PyObject_GetAttrString(loop, "call_later")))
    goto error;

  if(!(self->connections = PyObject_GetAttrString(app, "_connections")))
    goto error;

#ifdef REAPER_ENABLED
  if(!(self->check_idle = PyObject_GetAttrString((PyObject*)self, "_check_idle")))
    goto error;

  if(!Reaper_schedule_check_idle(self))
    goto error;
#endif

  goto finally;

  error:
  result = -1;

  finally:
  Py_XDECREF(loop);
  return result;
}