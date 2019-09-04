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
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  linebuf_reverse_index (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 

__attribute__((used)) static PyObject*
reverse_index(LineBuf *self, PyObject *args) {
#define reverse_index_doc "reverse_index(top, bottom) -> Scroll all lines in the range [top, bottom] by one down. After scrolling, top will be bottom."
    unsigned int top, bottom;
    if (!PyArg_ParseTuple(args, "II", &top, &bottom)) return NULL;
    linebuf_reverse_index(self, top, bottom);
    Py_RETURN_NONE;
}