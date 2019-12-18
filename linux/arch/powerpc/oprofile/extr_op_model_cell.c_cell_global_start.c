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
struct op_counter_config {int dummy; } ;

/* Variables and functions */
 scalar_t__ SPU_PROFILING_CYCLES ; 
 scalar_t__ SPU_PROFILING_EVENTS ; 
 int cell_global_start_ppu (struct op_counter_config*) ; 
 int cell_global_start_spu_cycles (struct op_counter_config*) ; 
 int cell_global_start_spu_events (struct op_counter_config*) ; 
 scalar_t__ profiling_mode ; 

__attribute__((used)) static int cell_global_start(struct op_counter_config *ctr)
{
	if (profiling_mode == SPU_PROFILING_CYCLES)
		return cell_global_start_spu_cycles(ctr);
	else if (profiling_mode == SPU_PROFILING_EVENTS)
		return cell_global_start_spu_events(ctr);
	else
		return cell_global_start_ppu(ctr);
}