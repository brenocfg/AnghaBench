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
typedef  int /*<<< orphan*/  index_type ;
struct TYPE_3__ {int continued; int has_dirty_text; int /*<<< orphan*/  gpu_cells; int /*<<< orphan*/  cpu_cells; } ;
typedef  TYPE_1__ Line ;
typedef  int /*<<< orphan*/  HistoryBuf ;

/* Variables and functions */
 int CONTINUED_MASK ; 
 int TEXT_DIRTY_MASK ; 
 int* attrptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_lineptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_lineptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
init_line(HistoryBuf *self, index_type num, Line *l) {
    // Initialize the line l, setting its pointer to the offsets for the line at index (buffer position) num
    l->cpu_cells = cpu_lineptr(self, num);
    l->gpu_cells = gpu_lineptr(self, num);
    l->continued = *attrptr(self, num) & CONTINUED_MASK;
    l->has_dirty_text = *attrptr(self, num) & TEXT_DIRTY_MASK ? true : false;
}