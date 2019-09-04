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
typedef  int /*<<< orphan*/  Line ;
typedef  int /*<<< orphan*/  Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  Cursor_Type ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,unsigned int*,unsigned int*,int*) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  line_apply_cursor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,unsigned int,int) ; 

__attribute__((used)) static PyObject*
apply_cursor(Line* self, PyObject *args) {
#define apply_cursor_doc "apply_cursor(cursor, at=0, num=1, clear_char=False) -> Apply the formatting attributes from cursor to the specified characters in this line."
    Cursor* cursor;
    unsigned int at=0, num=1;
    int clear_char = 0;
    if (!PyArg_ParseTuple(args, "O!|IIp", &Cursor_Type, &cursor, &at, &num, &clear_char)) return NULL;
    line_apply_cursor(self, cursor, at, num, clear_char & 1);
    Py_RETURN_NONE;
}