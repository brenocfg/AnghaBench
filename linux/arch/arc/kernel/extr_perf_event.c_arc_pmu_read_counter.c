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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_REG_PCT_CONTROL ; 
 int ARC_REG_PCT_CONTROL_SN ; 
 int /*<<< orphan*/  ARC_REG_PCT_INDEX ; 
 int /*<<< orphan*/  ARC_REG_PCT_SNAPH ; 
 int /*<<< orphan*/  ARC_REG_PCT_SNAPL ; 
 int read_aux_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_aux_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u64 arc_pmu_read_counter(int idx)
{
	u32 tmp;
	u64 result;

	/*
	 * ARC supports making 'snapshots' of the counters, so we don't
	 * need to care about counters wrapping to 0 underneath our feet
	 */
	write_aux_reg(ARC_REG_PCT_INDEX, idx);
	tmp = read_aux_reg(ARC_REG_PCT_CONTROL);
	write_aux_reg(ARC_REG_PCT_CONTROL, tmp | ARC_REG_PCT_CONTROL_SN);
	result = (u64) (read_aux_reg(ARC_REG_PCT_SNAPH)) << 32;
	result |= read_aux_reg(ARC_REG_PCT_SNAPL);

	return result;
}