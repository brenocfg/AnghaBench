#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  line_attrs_type ;
typedef  size_t index_type ;
struct TYPE_12__ {scalar_t__ num_segments; int xnum; scalar_t__ ynum; scalar_t__ count; size_t start_of_data; TYPE_2__* pagerhist; TYPE_1__* segments; } ;
struct TYPE_11__ {scalar_t__ end; scalar_t__ start; int rewrap_needed; } ;
struct TYPE_10__ {int /*<<< orphan*/  line_attrs; int /*<<< orphan*/  gpu_cells; int /*<<< orphan*/  cpu_cells; } ;
typedef  TYPE_3__ HistoryBuf ;
typedef  int /*<<< orphan*/  GPUCell ;
typedef  int /*<<< orphan*/  CPUCell ;

/* Variables and functions */
 int SEGMENT_SIZE ; 
 int /*<<< orphan*/  TEXT_DIRTY_MASK ; 
 int /*<<< orphan*/  add_segment (TYPE_3__*) ; 
 int /*<<< orphan*/ * attrptr (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rewrap_inner (TYPE_3__*,TYPE_3__*,scalar_t__,int /*<<< orphan*/ *,size_t*,size_t*) ; 

void historybuf_rewrap(HistoryBuf *self, HistoryBuf *other) {
    while(other->num_segments < self->num_segments) add_segment(other);
    if (other->xnum == self->xnum && other->ynum == self->ynum) {
        // Fast path
        for (index_type i = 0; i < self->num_segments; i++) {
            memcpy(other->segments[i].cpu_cells, self->segments[i].cpu_cells, SEGMENT_SIZE * self->xnum * sizeof(CPUCell));
            memcpy(other->segments[i].gpu_cells, self->segments[i].gpu_cells, SEGMENT_SIZE * self->xnum * sizeof(GPUCell));
            memcpy(other->segments[i].line_attrs, self->segments[i].line_attrs, SEGMENT_SIZE * sizeof(line_attrs_type));
        }
        other->count = self->count; other->start_of_data = self->start_of_data;
        return;
    }
    if (other->pagerhist && other->xnum != self->xnum && other->pagerhist->end != other->pagerhist->start)
        other->pagerhist->rewrap_needed = true;
    other->count = 0; other->start_of_data = 0;
    index_type x = 0, y = 0;
    if (self->count > 0) {
        rewrap_inner(self, other, self->count, NULL, &x, &y);
        for (index_type i = 0; i < other->count; i++) *attrptr(other, (other->start_of_data + i) % other->ynum) |= TEXT_DIRTY_MASK;
    }
}