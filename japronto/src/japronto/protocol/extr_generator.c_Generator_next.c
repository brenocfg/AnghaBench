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
struct TYPE_3__ {int /*<<< orphan*/  object; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ Generator ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_SetObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_StopIteration ; 

__attribute__((used)) static PyObject*
Generator_next(Generator* self)
{
  PyErr_SetObject(PyExc_StopIteration, self->object);

  return NULL;
}