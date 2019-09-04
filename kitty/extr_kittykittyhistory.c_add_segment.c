#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  line_attrs_type ;
struct TYPE_7__ {int num_segments; int xnum; TYPE_1__* segments; } ;
struct TYPE_6__ {int /*<<< orphan*/ * line_attrs; int /*<<< orphan*/ * gpu_cells; int /*<<< orphan*/ * cpu_cells; } ;
typedef  TYPE_1__ HistoryBufSegment ;
typedef  TYPE_2__ HistoryBuf ;
typedef  int /*<<< orphan*/  GPUCell ;
typedef  int /*<<< orphan*/  CPUCell ;

/* Variables and functions */
 void* PyMem_Calloc (int,int) ; 
 TYPE_1__* PyMem_Realloc (TYPE_1__*,int) ; 
 int SEGMENT_SIZE ; 
 int /*<<< orphan*/  fatal (char*) ; 

__attribute__((used)) static inline void
add_segment(HistoryBuf *self) {
    self->num_segments += 1;
    self->segments = PyMem_Realloc(self->segments, sizeof(HistoryBufSegment) * self->num_segments);
    if (self->segments == NULL) fatal("Out of memory allocating new history buffer segment");
    HistoryBufSegment *s = self->segments + self->num_segments - 1;
    s->cpu_cells = PyMem_Calloc(self->xnum * SEGMENT_SIZE, sizeof(CPUCell));
    s->gpu_cells = PyMem_Calloc(self->xnum * SEGMENT_SIZE, sizeof(GPUCell));
    s->line_attrs = PyMem_Calloc(SEGMENT_SIZE, sizeof(line_attrs_type));
    if (s->cpu_cells == NULL || s->gpu_cells == NULL || s->line_attrs == NULL) fatal("Out of memory allocating new history buffer segment");
}