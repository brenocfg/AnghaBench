#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t index_type ;
struct TYPE_12__ {size_t ynum; int continued; int has_dirty_text; int /*<<< orphan*/  xnum; } ;
struct TYPE_11__ {int* line_attrs; int /*<<< orphan*/ * line_map; int /*<<< orphan*/  xnum; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ LineBuf ;
typedef  TYPE_2__ Line ;

/* Variables and functions */
 int CONTINUED_MASK ; 
 int /*<<< orphan*/ * PyErr_NoMemory () ; 
 int /*<<< orphan*/  Py_CLEAR (TYPE_2__*) ; 
 int TEXT_DIRTY_MASK ; 
 TYPE_2__* alloc_line () ; 
 int /*<<< orphan*/  allocate_line_storage (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_line (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  init_line (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline PyObject*
create_line_copy_inner(LineBuf* self, index_type y) {
    Line src, *line;
    line = alloc_line();
    if (line == NULL) return PyErr_NoMemory();
    src.xnum = self->xnum; line->xnum = self->xnum;
    if (!allocate_line_storage(line, 0)) { Py_CLEAR(line); return PyErr_NoMemory(); }
    line->ynum = y;
    line->continued = self->line_attrs[y] & CONTINUED_MASK ? true : false;
    line->has_dirty_text = self->line_attrs[y] & TEXT_DIRTY_MASK ? true : false;
    init_line(self, &src, self->line_map[y]);
    copy_line(&src, line);
    return (PyObject*)line;
}