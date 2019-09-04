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
typedef  size_t uint8_t ;
struct TYPE_3__ {int dirty; int /*<<< orphan*/ * orig_color_table; int /*<<< orphan*/ * color_table; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ ColorProfile ;

/* Variables and functions */
 int PyLong_AsUnsignedLong (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 

__attribute__((used)) static PyObject*
reset_color(ColorProfile *self, PyObject *val) {
#define reset_color_doc "Reset the specified color"
    uint8_t i = PyLong_AsUnsignedLong(val) & 0xff;
    self->color_table[i] = self->orig_color_table[i];
    self->dirty = true;
    Py_RETURN_NONE;
}