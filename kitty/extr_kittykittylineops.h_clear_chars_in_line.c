#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t index_type ;
typedef  scalar_t__ char_type ;
struct TYPE_6__ {scalar_t__ ch; } ;
struct TYPE_5__ {int attrs; } ;
typedef  TYPE_1__ GPUCell ;
typedef  TYPE_2__ CPUCell ;

/* Variables and functions */

__attribute__((used)) static inline void
clear_chars_in_line(CPUCell *cpu_cells, GPUCell *gpu_cells, index_type xnum, char_type ch) {
    // Clear only the char part of each cell, the rest must have been cleared by a memset or similar
    if (ch) {
        for (index_type i = 0; i < xnum; i++) { cpu_cells[i].ch = ch; gpu_cells[i].attrs = 1; }
    }
}