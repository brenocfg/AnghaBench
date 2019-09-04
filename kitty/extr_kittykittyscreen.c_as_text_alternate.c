#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * linebuf; int /*<<< orphan*/ * main_linebuf; int /*<<< orphan*/ * alt_linebuf; } ;
typedef  TYPE_1__ Screen ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  LineBuf ;

/* Variables and functions */
 int /*<<< orphan*/ * as_text_generic_wrapper (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_line_ ; 

__attribute__((used)) static PyObject*
as_text_alternate(Screen *self, PyObject *args) {
    LineBuf *original = self->linebuf;
    self->linebuf = original == self->main_linebuf ? self->alt_linebuf : self->main_linebuf;
    PyObject *ans = as_text_generic_wrapper(self, args, range_line_);
    self->linebuf = original;
    return ans;
}