#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {unsigned int ynum; int continued; int has_dirty_text; int /*<<< orphan*/  xnum; } ;
struct TYPE_9__ {int* line_attrs; int /*<<< orphan*/ * line_map; int /*<<< orphan*/  xnum; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ LineBuf ;
typedef  TYPE_2__ Line ;

/* Variables and functions */
 int CONTINUED_MASK ; 
 int /*<<< orphan*/  Line_Type ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,unsigned int*,int /*<<< orphan*/ *,TYPE_2__**) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int TEXT_DIRTY_MASK ; 
 int /*<<< orphan*/  copy_line (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  init_line (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject*
copy_line_to(LineBuf *self, PyObject *args) {
#define copy_line_to_doc "Copy the line at ynum to the provided line object."
    unsigned int y;
    Line src, *dest;
    if (!PyArg_ParseTuple(args, "IO!", &y, &Line_Type, &dest)) return NULL;
    src.xnum = self->xnum; dest->xnum = self->xnum;
    dest->ynum = y;
    dest->continued = self->line_attrs[y] & CONTINUED_MASK;
    dest->has_dirty_text = self->line_attrs[y] & TEXT_DIRTY_MASK;
    init_line(self, &src, self->line_map[y]);
    copy_line(&src, dest);
    Py_RETURN_NONE;
}