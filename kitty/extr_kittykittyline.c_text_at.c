#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int xnum; scalar_t__ cpu_cells; } ;
typedef  scalar_t__ Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ Line ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_IndexError ; 
 int /*<<< orphan*/ * cell_text (scalar_t__) ; 

__attribute__((used)) static PyObject*
text_at(Line* self, Py_ssize_t xval) {
#define text_at_doc "[x] -> Return the text in the specified cell"
    if ((unsigned)xval >= self->xnum) { PyErr_SetString(PyExc_IndexError, "Column number out of bounds"); return NULL; }
    return cell_text(self->cpu_cells + xval);
}