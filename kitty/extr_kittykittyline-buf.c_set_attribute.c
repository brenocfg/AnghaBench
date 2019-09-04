#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  LineBuf ;

/* Variables and functions */
 unsigned int DECORATION_SHIFT ; 
 unsigned int DIM_SHIFT ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  linebuf_set_attribute (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 

__attribute__((used)) static PyObject*
set_attribute(LineBuf *self, PyObject *args) {
#define set_attribute_doc "set_attribute(which, val) -> Set the attribute on all cells in the line."
    unsigned int shift, val;
    if (!PyArg_ParseTuple(args, "II", &shift, &val)) return NULL;
    if (shift < DECORATION_SHIFT || shift > DIM_SHIFT) { PyErr_SetString(PyExc_ValueError, "Unknown attribute"); return NULL; }
    linebuf_set_attribute(self, shift, val);
    Py_RETURN_NONE;
}