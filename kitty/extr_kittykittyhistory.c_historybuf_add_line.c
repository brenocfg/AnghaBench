#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  index_type ;
struct TYPE_9__ {int /*<<< orphan*/  line; } ;
struct TYPE_8__ {int continued; scalar_t__ has_dirty_text; } ;
typedef  TYPE_1__ Line ;
typedef  TYPE_2__ HistoryBuf ;

/* Variables and functions */
 int CONTINUED_MASK ; 
 int TEXT_DIRTY_MASK ; 
 int* attrptr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_line (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  historybuf_push (TYPE_2__*) ; 

void
historybuf_add_line(HistoryBuf *self, const Line *line) {
    index_type idx = historybuf_push(self);
    copy_line(line, self->line);
    *attrptr(self, idx) = (line->continued & CONTINUED_MASK) | (line->has_dirty_text ? TEXT_DIRTY_MASK : 0);
}