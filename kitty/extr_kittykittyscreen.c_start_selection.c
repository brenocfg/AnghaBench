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
 int EXTEND_CELL ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,unsigned int*,unsigned int*,int*,int*) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  screen_start_selection (int /*<<< orphan*/ *,unsigned int,unsigned int,int,int) ; 

__attribute__((used)) static PyObject*
start_selection(Screen *self, PyObject *args) {
    unsigned int x, y;
    int rectangle_select = 0, extend_mode = EXTEND_CELL;
    if (!PyArg_ParseTuple(args, "II|pi", &x, &y, &rectangle_select, &extend_mode)) return NULL;
    screen_start_selection(self, x, y, rectangle_select, extend_mode);
    Py_RETURN_NONE;
}