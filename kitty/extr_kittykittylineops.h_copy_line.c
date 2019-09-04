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
struct TYPE_4__ {int /*<<< orphan*/  xnum; int /*<<< orphan*/  gpu_cells; int /*<<< orphan*/  cpu_cells; } ;
typedef  TYPE_1__ Line ;
typedef  int /*<<< orphan*/  GPUCell ;
typedef  int /*<<< orphan*/  CPUCell ;

/* Variables and functions */
 int MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
copy_line(const Line *src, Line *dest) {
    memcpy(dest->cpu_cells, src->cpu_cells, sizeof(CPUCell) * MIN(src->xnum, dest->xnum));
    memcpy(dest->gpu_cells, src->gpu_cells, sizeof(GPUCell) * MIN(src->xnum, dest->xnum));
}