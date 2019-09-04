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
struct TYPE_3__ {int gpu_cells; int cpu_cells; } ;
typedef  TYPE_1__ Line ;
typedef  int /*<<< orphan*/  GPUCell ;
typedef  int /*<<< orphan*/  CPUCell ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline void
line_save_cells(Line *line, index_type start, index_type num, GPUCell *gpu_cells, CPUCell *cpu_cells) {
    memcpy(gpu_cells + start, line->gpu_cells + start, sizeof(GPUCell) * num);
    memcpy(cpu_cells + start, line->cpu_cells + start, sizeof(CPUCell) * num);
}