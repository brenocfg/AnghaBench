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
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,unsigned int*,int*) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  screen_set_mode (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static PyObject*
set_mode(Screen *self, PyObject *args) {
    int private = false;
    unsigned int mode;
    if (!PyArg_ParseTuple(args, "I|p", &mode, &private)) return NULL;
    if (private) mode <<= 5;
    screen_set_mode(self, mode);
    Py_RETURN_NONE;
}