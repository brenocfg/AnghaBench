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
typedef  int /*<<< orphan*/  HistoryBuf ;

/* Variables and functions */
 int /*<<< orphan*/  Line_Type ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  historybuf_add_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject*
push(HistoryBuf *self, PyObject *args) {
#define push_doc "Push a line into this buffer, removing the oldest line, if necessary"
    Line *line;
    if (!PyArg_ParseTuple(args, "O!", &Line_Type, &line)) return NULL;
    historybuf_add_line(self, line);
    Py_RETURN_NONE;
}