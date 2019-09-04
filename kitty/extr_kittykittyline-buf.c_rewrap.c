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
typedef  int /*<<< orphan*/  index_type ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  LineBuf ;
typedef  int /*<<< orphan*/  HistoryBuf ;

/* Variables and functions */
 int /*<<< orphan*/  HistoryBuf_Type ; 
 int /*<<< orphan*/  LineBuf_Type ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  linebuf_rewrap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*,unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject*
rewrap(LineBuf *self, PyObject *args) {
    LineBuf* other;
    HistoryBuf *historybuf;
    unsigned int nclb, ncla;

    if (!PyArg_ParseTuple(args, "O!O!", &LineBuf_Type, &other, &HistoryBuf_Type, &historybuf)) return NULL;
    index_type x = 0, y = 0;
    linebuf_rewrap(self, other, &nclb, &ncla, historybuf, &x, &y);

    return Py_BuildValue("II", nclb, ncla);
}