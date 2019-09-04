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
struct TYPE_4__ {unsigned int xnum; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ Line ;
typedef  int /*<<< orphan*/  Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  Cursor_Type ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,unsigned int*,int*,unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  line_set_char (TYPE_1__*,unsigned int,int,unsigned int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static PyObject*
set_char(Line *self, PyObject *args) {
#define set_char_doc "set_char(at, ch, width=1, cursor=None) -> Set the character at the specified cell. If cursor is not None, also set attributes from that cursor."
    unsigned int at, width=1;
    int ch;
    Cursor *cursor = NULL;

    if (!PyArg_ParseTuple(args, "IC|IO!", &at, &ch, &width, &Cursor_Type, &cursor)) return NULL;
    if (at >= self->xnum) {
        PyErr_SetString(PyExc_ValueError, "Out of bounds");
        return NULL;
    }
    line_set_char(self, at, ch, width, cursor, false);
    Py_RETURN_NONE;
}