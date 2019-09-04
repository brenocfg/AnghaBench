#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sprite_z; int /*<<< orphan*/  sprite_y; int /*<<< orphan*/  sprite_x; } ;
struct TYPE_4__ {unsigned long xnum; TYPE_2__* gpu_cells; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ Line ;
typedef  TYPE_2__ GPUCell ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_IndexError ; 
 unsigned long PyLong_AsUnsignedLong (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject*
sprite_at(Line* self, PyObject *x) {
#define sprite_at_doc "[x] -> Return the sprite in the specified cell"
    unsigned long xval = PyLong_AsUnsignedLong(x);
    if (xval >= self->xnum) { PyErr_SetString(PyExc_IndexError, "Column number out of bounds"); return NULL; }
    GPUCell *c = self->gpu_cells + xval;
    return Py_BuildValue("HHH", c->sprite_x, c->sprite_y, c->sprite_z);
}