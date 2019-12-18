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
struct TYPE_5__ {int /*<<< orphan*/  observation_indices; int /*<<< orphan*/  env_c_api; int /*<<< orphan*/  level_cache_context; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ LabObject ;

/* Variables and functions */
 TYPE_3__* Py_TYPE (TYPE_1__*) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  env_close (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void LabObject_dealloc(PyObject* pself) {
  LabObject* self = (LabObject*)pself;
  env_close(self);
  Py_XDECREF(self->level_cache_context);
  free(self->env_c_api);
  free(self->observation_indices);
  Py_TYPE(self)->tp_free(pself);
}