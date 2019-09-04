#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  highlight_bg; int /*<<< orphan*/  highlight_fg; int /*<<< orphan*/  cursor_text_uses_bg; int /*<<< orphan*/  cursor_text_color; int /*<<< orphan*/  cursor_color; int /*<<< orphan*/  default_bg; int /*<<< orphan*/  default_fg; } ;
struct TYPE_5__ {int dirty; TYPE_1__ configured; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ ColorProfile ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 

__attribute__((used)) static PyObject*
set_configured_colors(ColorProfile *self, PyObject *args) {
#define set_configured_colors_doc "Set the configured colors"
    if (!PyArg_ParseTuple(
                args, "II|IIIII",
                &(self->configured.default_fg), &(self->configured.default_bg),
                &(self->configured.cursor_color), &(self->configured.cursor_text_color), &(self->configured.cursor_text_uses_bg),
                &(self->configured.highlight_fg), &(self->configured.highlight_bg))) return NULL;
    self->dirty = true;
    Py_RETURN_NONE;
}