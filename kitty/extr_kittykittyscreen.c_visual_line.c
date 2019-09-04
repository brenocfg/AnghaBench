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
struct TYPE_4__ {unsigned int lines; } ;
typedef  TYPE_1__ Screen ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,unsigned int*) ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  visual_line_ (TYPE_1__*,unsigned int) ; 

__attribute__((used)) static PyObject*
visual_line(Screen *self, PyObject *args) {
    // The line corresponding to the yth visual line, taking into account scrolling
    unsigned int y;
    if (!PyArg_ParseTuple(args, "I", &y)) return NULL;
    if (y >= self->lines) { Py_RETURN_NONE; }
    return Py_BuildValue("O", visual_line_(self, y));
}