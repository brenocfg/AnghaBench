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
typedef  scalar_t__ index_type ;
struct TYPE_4__ {scalar_t__ num_segments; scalar_t__ ynum; } ;
typedef  TYPE_1__ HistoryBuf ;

/* Variables and functions */
 scalar_t__ SEGMENT_SIZE ; 
 scalar_t__ UNLIKELY (int) ; 
 int /*<<< orphan*/  add_segment (TYPE_1__*) ; 
 int /*<<< orphan*/  fatal (char*,scalar_t__) ; 

__attribute__((used)) static inline index_type
segment_for(HistoryBuf *self, index_type y) {
    index_type seg_num = y / SEGMENT_SIZE;
    while (UNLIKELY(seg_num >= self->num_segments && SEGMENT_SIZE * self->num_segments < self->ynum)) add_segment(self);
    if (UNLIKELY(seg_num >= self->num_segments)) fatal("Out of bounds access to history buffer line number: %u", y);
    return seg_num;
}