#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ (* tp_alloc ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/ * check_interval; int /*<<< orphan*/ * check_idle_handle; int /*<<< orphan*/ * check_idle; int /*<<< orphan*/ * call_later; int /*<<< orphan*/ * connections; } ;
typedef  TYPE_1__ Reaper ;
typedef  TYPE_2__ PyTypeObject ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject*
Reaper_new(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
  Reaper* self = NULL;

  self = (Reaper*)type->tp_alloc(type, 0);
  if(!self)
    goto finally;

  self->connections = NULL;
  self->call_later = NULL;
  self->check_idle = NULL;
  self->check_idle_handle = NULL;
  self->check_interval = NULL;

  finally:
  return (PyObject*)self;
}