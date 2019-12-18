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
 int ARRAY_SIZE (int*) ; 
 scalar_t__ rk3288_cru_base ; 
 int* rk3288_saved_cru_reg_ids ; 
 int* rk3288_saved_cru_regs ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void rk3288_clk_resume(void)
{
	int i, reg_id;

	for (i = ARRAY_SIZE(rk3288_saved_cru_reg_ids) - 1; i >= 0; i--) {
		reg_id = rk3288_saved_cru_reg_ids[i];

		writel_relaxed(rk3288_saved_cru_regs[i] | 0xffff0000,
			       rk3288_cru_base + reg_id);
	}
}