#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t index_type ;
typedef  void* color_type ;
typedef  int /*<<< orphan*/  char_type ;
struct TYPE_11__ {int fg; int bg; int decoration_fg; size_t x; } ;
struct TYPE_10__ {size_t xnum; TYPE_2__* cpu_cells; TYPE_1__* gpu_cells; } ;
struct TYPE_9__ {int /*<<< orphan*/  cc_idx; int /*<<< orphan*/  ch; } ;
struct TYPE_8__ {void* decoration_fg; void* bg; void* fg; int /*<<< orphan*/  attrs; } ;
typedef  scalar_t__ Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_3__ Line ;
typedef  TYPE_4__ Cursor ;

/* Variables and functions */
 int COL_MASK ; 
 int /*<<< orphan*/  CURSOR_TO_ATTRS (TYPE_4__*,int) ; 
 int /*<<< orphan*/  Cursor_Type ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,TYPE_4__**) ; 
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 void* PyUnicode_DATA (int /*<<< orphan*/ *) ; 
 scalar_t__ PyUnicode_GET_LENGTH (int /*<<< orphan*/ *) ; 
 int PyUnicode_KIND (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyUnicode_READ (int,void*,scalar_t__) ; 
 scalar_t__ PyUnicode_READY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static PyObject*
set_text(Line* self, PyObject *args) {
#define set_text_doc "set_text(src, offset, sz, cursor) -> Set the characters and attributes from the specified text and cursor"
    PyObject *src;
    Py_ssize_t offset, sz, limit;
    char_type attrs;
    Cursor *cursor;
    int kind;
    void *buf;

    if (!PyArg_ParseTuple(args, "UnnO!", &src, &offset, &sz, &Cursor_Type, &cursor)) return NULL;
    if (PyUnicode_READY(src) != 0) {
        PyErr_NoMemory();
        return NULL;
    }
    kind = PyUnicode_KIND(src);
    buf = PyUnicode_DATA(src);
    limit = offset + sz;
    if (PyUnicode_GET_LENGTH(src) < limit) {
        PyErr_SetString(PyExc_ValueError, "Out of bounds offset/sz");
        return NULL;
    }
    attrs = CURSOR_TO_ATTRS(cursor, 1);
    color_type fg = (cursor->fg & COL_MASK), bg = cursor->bg & COL_MASK;
    color_type dfg = cursor->decoration_fg & COL_MASK;

    for (index_type i = cursor->x; offset < limit && i < self->xnum; i++, offset++) {
        self->cpu_cells[i].ch = (PyUnicode_READ(kind, buf, offset));
        self->gpu_cells[i].attrs = attrs;
        self->gpu_cells[i].fg = fg;
        self->gpu_cells[i].bg = bg;
        self->gpu_cells[i].decoration_fg = dfg;
        memset(self->cpu_cells[i].cc_idx, 0, sizeof(self->cpu_cells[i].cc_idx));
    }

    Py_RETURN_NONE;
}