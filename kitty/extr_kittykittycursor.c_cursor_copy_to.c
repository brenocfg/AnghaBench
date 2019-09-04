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
struct TYPE_4__ {int /*<<< orphan*/  decoration_fg; int /*<<< orphan*/  bg; int /*<<< orphan*/  fg; int /*<<< orphan*/  decoration; int /*<<< orphan*/  reverse; int /*<<< orphan*/  dim; int /*<<< orphan*/  strikethrough; int /*<<< orphan*/  italic; int /*<<< orphan*/  bold; int /*<<< orphan*/  blink; int /*<<< orphan*/  shape; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ Cursor ;

/* Variables and functions */

void cursor_copy_to(Cursor *src, Cursor *dest) {
#define CCY(x) dest->x = src->x;
    CCY(x); CCY(y); CCY(shape); CCY(blink);
    CCY(bold); CCY(italic); CCY(strikethrough); CCY(dim); CCY(reverse); CCY(decoration); CCY(fg); CCY(bg); CCY(decoration_fg);
}