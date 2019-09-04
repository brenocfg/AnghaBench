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
typedef  int /*<<< orphan*/  LineBuf ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  linebuf_insert_lines (int /*<<< orphan*/ *,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static PyObject*
insert_lines(LineBuf *self, PyObject *args) {
#define insert_lines_doc "insert_lines(num, y, bottom) -> Insert num blank lines at y, only changing lines in the range [y, bottom]."
    unsigned int y, num, bottom;
    if (!PyArg_ParseTuple(args, "III", &num, &y, &bottom)) return NULL;
    linebuf_insert_lines(self, num, y, bottom);
    Py_RETURN_NONE;
}