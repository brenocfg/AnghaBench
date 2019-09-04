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
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,unsigned int*,int*,int*) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  screen_cursor_up (int /*<<< orphan*/ *,unsigned int,int,int) ; 

__attribute__((used)) static PyObject*
cursor_up(Screen *self, PyObject *args) {
    unsigned int count = 1;
    int do_carriage_return = false, move_direction = -1;
    if (!PyArg_ParseTuple(args, "|Ipi", &count, &do_carriage_return, &move_direction)) return NULL;
    screen_cursor_up(self, count, do_carriage_return, move_direction);
    Py_RETURN_NONE;
}