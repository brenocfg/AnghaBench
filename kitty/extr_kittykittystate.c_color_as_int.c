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
typedef  int color_type ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int PyLong_AsUnsignedLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyTuple_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyTuple_GET_ITEM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * Py_None ; 
 int default_color ; 

__attribute__((used)) static inline color_type
color_as_int(PyObject *color) {
    if (color == Py_None && default_color) return default_color;
    if (!PyTuple_Check(color)) { PyErr_SetString(PyExc_TypeError, "Not a color tuple"); return 0; }
#define I(n, s) ((PyLong_AsUnsignedLong(PyTuple_GET_ITEM(color, n)) & 0xff) << s)
    return (I(0, 16) | I(1, 8) | I(2, 0)) & 0xffffff;
#undef I
}