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
struct TYPE_3__ {size_t shape; int /*<<< orphan*/  decoration_fg; int /*<<< orphan*/  decoration; int /*<<< orphan*/  dim; int /*<<< orphan*/  strikethrough; int /*<<< orphan*/  reverse; int /*<<< orphan*/  italic; int /*<<< orphan*/  bold; int /*<<< orphan*/  bg; int /*<<< orphan*/  fg; int /*<<< orphan*/  blink; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  BOOL (int /*<<< orphan*/ ) ; 
 size_t NUM_OF_CURSOR_SHAPES ; 
 int /*<<< orphan*/ * PyUnicode_FromFormat (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char** cursor_names ; 

__attribute__((used)) static PyObject *
repr(Cursor *self) {
    return PyUnicode_FromFormat(
        "Cursor(x=%u, y=%u, shape=%s, blink=%R, fg=#%08x, bg=#%08x, bold=%R, italic=%R, reverse=%R, strikethrough=%R, dim=%R, decoration=%d, decoration_fg=#%08x)",
        self->x, self->y, (self->shape < NUM_OF_CURSOR_SHAPES ? cursor_names[self->shape] : "INVALID"),
        BOOL(self->blink), self->fg, self->bg, BOOL(self->bold), BOOL(self->italic), BOOL(self->reverse), BOOL(self->strikethrough), BOOL(self->dim), self->decoration, self->decoration_fg
    );
}