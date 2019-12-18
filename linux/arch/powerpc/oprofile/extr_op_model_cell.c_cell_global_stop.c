#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ PPU_PROFILING ; 
 scalar_t__ SPU_PROFILING_EVENTS ; 
 int /*<<< orphan*/  cell_global_stop_ppu () ; 
 int /*<<< orphan*/  cell_global_stop_spu_cycles () ; 
 int /*<<< orphan*/  cell_global_stop_spu_events () ; 
 scalar_t__ profiling_mode ; 

__attribute__((used)) static void cell_global_stop(void)
{
	if (profiling_mode == PPU_PROFILING)
		cell_global_stop_ppu();
	else if (profiling_mode == SPU_PROFILING_EVENTS)
		cell_global_stop_spu_events();
	else
		cell_global_stop_spu_cycles();
}