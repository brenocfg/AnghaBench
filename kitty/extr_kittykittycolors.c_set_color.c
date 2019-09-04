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
struct TYPE_3__ {unsigned long* color_table; int dirty; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ ColorProfile ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,unsigned char*,unsigned long*) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 

__attribute__((used)) static PyObject*
set_color(ColorProfile *self, PyObject *args) {
#define set_color_doc "Set the specified color"
    unsigned char i;
    unsigned long val;
    if (!PyArg_ParseTuple(args, "Bk", &i, &val)) return NULL;
    self->color_table[i] = val;
    self->dirty = true;
    Py_RETURN_NONE;
}