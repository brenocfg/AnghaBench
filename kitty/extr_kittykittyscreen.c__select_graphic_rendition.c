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
typedef  int /*<<< orphan*/  Screen ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 unsigned int PyLong_AsUnsignedLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyTuple_GET_ITEM (int /*<<< orphan*/ *,int) ; 
 int PyTuple_GET_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  select_graphic_rendition (int /*<<< orphan*/ *,unsigned int*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject*
_select_graphic_rendition(Screen *self, PyObject *args) {
    unsigned int params[256] = {0};
    for (int i = 0; i < PyTuple_GET_SIZE(args); i++) { params[i] = PyLong_AsUnsignedLong(PyTuple_GET_ITEM(args, i)); }
    select_graphic_rendition(self, params, PyTuple_GET_SIZE(args), NULL);
    Py_RETURN_NONE;
}