#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int index_type ;
struct TYPE_7__ {int /*<<< orphan*/ * line; } ;
struct TYPE_6__ {int /*<<< orphan*/ * line; } ;
struct TYPE_5__ {int scrolled_by; TYPE_3__* linebuf; TYPE_4__* historybuf; } ;
typedef  TYPE_1__ Screen ;
typedef  int /*<<< orphan*/  Line ;

/* Variables and functions */
 int /*<<< orphan*/  historybuf_init_line (TYPE_4__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linebuf_init_line (TYPE_3__*,int) ; 

__attribute__((used)) static inline Line*
visual_line_(Screen *self, index_type y) {
    if (self->scrolled_by) {
        if (y < self->scrolled_by) {
            historybuf_init_line(self->historybuf, self->scrolled_by - 1 - y, self->historybuf->line);
            return self->historybuf->line;
        }
        y -= self->scrolled_by;
    }
    linebuf_init_line(self->linebuf, y);
    return self->linebuf->line;
}