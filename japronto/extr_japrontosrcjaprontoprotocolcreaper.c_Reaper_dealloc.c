#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* tp_free ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  connections; int /*<<< orphan*/  call_later; int /*<<< orphan*/  check_idle; int /*<<< orphan*/  check_idle_handle; int /*<<< orphan*/  check_interval; } ;
typedef  TYPE_1__ Reaper ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 TYPE_3__* Py_TYPE (TYPE_1__*) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
Reaper_dealloc(Reaper* self)
{
  Py_XDECREF(self->check_interval);
  Py_XDECREF(self->check_idle_handle);
  Py_XDECREF(self->check_idle);
  Py_XDECREF(self->call_later);
  Py_XDECREF(self->connections);

  Py_TYPE(self)->tp_free((PyObject*)self);
}