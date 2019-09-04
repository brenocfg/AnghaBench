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
struct TYPE_3__ {int dirty; int /*<<< orphan*/ * color_table; int /*<<< orphan*/ * orig_color_table; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ ColorProfile ;

/* Variables and functions */
 int /*<<< orphan*/  FG_BG_256 ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  PyList_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyList_GET_ITEM (int /*<<< orphan*/ *,size_t) ; 
 size_t PyList_GET_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyLong_AsUnsignedLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 size_t arraysz (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject*
update_ansi_color_table(ColorProfile *self, PyObject *val) {
#define update_ansi_color_table_doc "Update the 256 basic colors"
    if (!PyList_Check(val)) { PyErr_SetString(PyExc_TypeError, "color table must be a list"); return NULL; }
    if (PyList_GET_SIZE(val) != arraysz(FG_BG_256)) { PyErr_SetString(PyExc_TypeError, "color table must have 256 items"); return NULL; }
    for (size_t i = 0; i < arraysz(FG_BG_256); i++) {
        self->color_table[i] = PyLong_AsUnsignedLong(PyList_GET_ITEM(val, i));
        self->orig_color_table[i] = self->color_table[i];
    }
    self->dirty = true;
    Py_RETURN_NONE;
}