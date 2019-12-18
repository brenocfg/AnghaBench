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
typedef  int u32 ;

/* Variables and functions */
 int CPU_FINETRIM_1_FCPU_1 ; 
 int CPU_FINETRIM_1_FCPU_2 ; 
 int CPU_FINETRIM_1_FCPU_3 ; 
 int CPU_FINETRIM_1_FCPU_4 ; 
 int CPU_FINETRIM_1_FCPU_5 ; 
 int CPU_FINETRIM_1_FCPU_6 ; 
 scalar_t__ CPU_FINETRIM_DR ; 
 scalar_t__ CPU_FINETRIM_R ; 
 int CPU_FINETRIM_R_FCPU_1_MASK ; 
 int CPU_FINETRIM_R_FCPU_2_MASK ; 
 int CPU_FINETRIM_R_FCPU_3_MASK ; 
 int CPU_FINETRIM_R_FCPU_4_MASK ; 
 int CPU_FINETRIM_R_FCPU_5_MASK ; 
 int CPU_FINETRIM_R_FCPU_6_MASK ; 
 scalar_t__ clk_base ; 
 int /*<<< orphan*/  tegra114_clock_tune_cpu_trimmers_low () ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

void tegra114_clock_tune_cpu_trimmers_init(void)
{
	u32 dr = 0, r = 0;

	/* Increment the rise->rise clock delay by four steps */
	r |= (CPU_FINETRIM_R_FCPU_1_MASK | CPU_FINETRIM_R_FCPU_2_MASK |
	      CPU_FINETRIM_R_FCPU_3_MASK | CPU_FINETRIM_R_FCPU_4_MASK |
	      CPU_FINETRIM_R_FCPU_5_MASK | CPU_FINETRIM_R_FCPU_6_MASK);
	writel_relaxed(r, clk_base + CPU_FINETRIM_R);

	/*
	 * Use the rise->rise clock propagation delay specified in the
	 * r field
	 */
	dr |= (CPU_FINETRIM_1_FCPU_1 | CPU_FINETRIM_1_FCPU_2 |
	       CPU_FINETRIM_1_FCPU_3 | CPU_FINETRIM_1_FCPU_4 |
	       CPU_FINETRIM_1_FCPU_5 | CPU_FINETRIM_1_FCPU_6);
	writel_relaxed(dr, clk_base + CPU_FINETRIM_DR);

	tegra114_clock_tune_cpu_trimmers_low();
}