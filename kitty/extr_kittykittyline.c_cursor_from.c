#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  char_type ;
struct TYPE_9__ {unsigned int x; unsigned int y; int decoration_fg; int /*<<< orphan*/  bg; int /*<<< orphan*/  fg; } ;
struct TYPE_8__ {unsigned int xnum; TYPE_1__* gpu_cells; } ;
struct TYPE_7__ {int decoration_fg; int /*<<< orphan*/  bg; int /*<<< orphan*/  fg; int /*<<< orphan*/  attrs; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ Line ;
typedef  TYPE_3__ Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  ATTRS_TO_CURSOR (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int COL_MASK ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 TYPE_3__* alloc_cursor () ; 

__attribute__((used)) static PyObject*
cursor_from(Line* self, PyObject *args) {
#define cursor_from_doc "cursor_from(x, y=0) -> Create a cursor object based on the formatting attributes at the specified x position. The y value of the cursor is set as specified."
    unsigned int x, y = 0;
    Cursor* ans;
    if (!PyArg_ParseTuple(args, "I|I", &x, &y)) return NULL;
    if (x >= self->xnum) {
        PyErr_SetString(PyExc_ValueError, "Out of bounds x");
        return NULL;
    }
    ans = alloc_cursor();
    if (ans == NULL) { PyErr_NoMemory(); return NULL; }
    ans->x = x; ans->y = y;
    char_type attrs = self->gpu_cells[x].attrs;
    ATTRS_TO_CURSOR(attrs, ans);
    ans->fg = self->gpu_cells[x].fg; ans->bg = self->gpu_cells[x].bg;
    ans->decoration_fg = self->gpu_cells[x].decoration_fg & COL_MASK;

    return (PyObject*)ans;
}