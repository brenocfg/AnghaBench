#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ index_type ;
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_11__ {scalar_t__ xnum; TYPE_1__ member_0; } ;
struct TYPE_10__ {scalar_t__ xnum; int ynum; scalar_t__* line_map; int /*<<< orphan*/ * line_attrs; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ LineBuf ;
typedef  TYPE_3__ Line ;

/* Variables and functions */
 int /*<<< orphan*/  LineBuf_Type ; 
 scalar_t__ MIN (int,int) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  PyObject_TypeCheck (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  copy_line (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  init_line (TYPE_2__*,TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static PyObject*
copy_old(LineBuf *self, PyObject *y) {
    if (!PyObject_TypeCheck(y, &LineBuf_Type)) { PyErr_SetString(PyExc_TypeError, "Not a LineBuf object"); return NULL; }
    LineBuf *other = (LineBuf*)y;
    if (other->xnum != self->xnum) { PyErr_SetString(PyExc_ValueError, "LineBuf has a different number of columns"); return NULL; }
    Line sl = {{0}}, ol = {{0}};
    sl.xnum = self->xnum; ol.xnum = other->xnum;

    for (index_type i = 0; i < MIN(self->ynum, other->ynum); i++) {
        index_type s = self->ynum - 1 - i, o = other->ynum - 1 - i;
        self->line_attrs[s] = other->line_attrs[o];
        s = self->line_map[s]; o = other->line_map[o];
        init_line(self, &sl, s); init_line(other, &ol, o);
        copy_line(&ol, &sl);
    }
    Py_RETURN_NONE;
}