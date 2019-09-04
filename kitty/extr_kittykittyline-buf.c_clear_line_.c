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
typedef  int index_type ;
struct TYPE_3__ {int has_dirty_text; int /*<<< orphan*/  gpu_cells; int /*<<< orphan*/  cpu_cells; } ;
typedef  TYPE_1__ Line ;
typedef  int /*<<< orphan*/  GPUCell ;
typedef  int /*<<< orphan*/  CPUCell ;

/* Variables and functions */
 scalar_t__ BLANK_CHAR ; 
 int /*<<< orphan*/  clear_chars_in_line (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
clear_line_(Line *l, index_type xnum) {
    memset(l->cpu_cells, 0, xnum * sizeof(CPUCell));
    memset(l->gpu_cells, 0, xnum * sizeof(GPUCell));
    if (BLANK_CHAR != 0) clear_chars_in_line(l->cpu_cells, l->gpu_cells, xnum, BLANK_CHAR);
    l->has_dirty_text = false;
}