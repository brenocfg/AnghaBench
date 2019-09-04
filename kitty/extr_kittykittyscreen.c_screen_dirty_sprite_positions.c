#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ index_type ;
struct TYPE_5__ {scalar_t__ count; } ;
struct TYPE_4__ {int is_dirty; scalar_t__ lines; TYPE_3__* historybuf; int /*<<< orphan*/  alt_linebuf; int /*<<< orphan*/  main_linebuf; } ;
typedef  TYPE_1__ Screen ;

/* Variables and functions */
 int /*<<< orphan*/  historybuf_mark_line_dirty (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  linebuf_mark_line_dirty (int /*<<< orphan*/ ,scalar_t__) ; 

void
screen_dirty_sprite_positions(Screen *self) {
    self->is_dirty = true;
    for (index_type i = 0; i < self->lines; i++) {
        linebuf_mark_line_dirty(self->main_linebuf, i);
        linebuf_mark_line_dirty(self->alt_linebuf, i);
    }
    for (index_type i = 0; i < self->historybuf->count; i++) historybuf_mark_line_dirty(self->historybuf, i);
}