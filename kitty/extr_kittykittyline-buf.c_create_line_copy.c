#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ index_type ;
struct TYPE_4__ {scalar_t__ ynum; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ LineBuf ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  PyLong_AsUnsignedLong (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_line_copy_inner (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static PyObject*
create_line_copy(LineBuf *self, PyObject *ynum) {
#define create_line_copy_doc "Create a new Line object that is a copy of the line at ynum. Note that this line has its own copy of the data and does not refer to the data in the LineBuf."
    index_type y = (index_type)PyLong_AsUnsignedLong(ynum);
    if (y >= self->ynum) { PyErr_SetString(PyExc_ValueError, "Out of bounds"); return NULL; }
    return create_line_copy_inner(self, y);
}