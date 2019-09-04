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
struct TYPE_6__ {int /*<<< orphan*/  status; int /*<<< orphan*/ * env_c_api; } ;
struct TYPE_5__ {scalar_t__ (* tp_alloc ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ PyTypeObject ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ LabObject ;

/* Variables and functions */
 int /*<<< orphan*/  ENV_STATUS_CLOSED ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_MemoryError ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 scalar_t__ stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject* LabObject_new(PyTypeObject* type, PyObject* args,
                               PyObject* kwds) {
  LabObject* self;

  self = (LabObject*)type->tp_alloc(type, 0);
  if (self != NULL) {
    self->env_c_api = calloc(1, sizeof *self->env_c_api);

    if (self->env_c_api == NULL) {
      PyErr_SetString(PyExc_MemoryError, "malloc failed.");
      return NULL;
    }
    self->status = ENV_STATUS_CLOSED;
  }
  return (PyObject*)self;
}