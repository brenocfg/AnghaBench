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
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int*,char**) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  write_escape_code_to_child (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static PyObject*
send_escape_code_to_child(Screen *self, PyObject *args) {
    int code;
    char *text;
    if (!PyArg_ParseTuple(args, "is", &code, &text)) return NULL;
    write_escape_code_to_child(self, code, text);
    Py_RETURN_NONE;
}