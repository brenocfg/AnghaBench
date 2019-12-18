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
struct clk {int bits; int /*<<< orphan*/  module; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWDCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PWDCR_EN_XRX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PWDSR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PWDSR_XRX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_pmu_lock ; 
 scalar_t__ of_machine_is_compatible (char*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int pmu_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmu_w32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pmu_enable(struct clk *clk)
{
	int retry = 1000000;

	if (of_machine_is_compatible("lantiq,ar10")
	    || of_machine_is_compatible("lantiq,grx390")) {
		pmu_w32(clk->bits, PWDCR_EN_XRX(clk->module));
		do {} while (--retry &&
			     (!(pmu_r32(PWDSR_XRX(clk->module)) & clk->bits)));

	} else {
		spin_lock(&g_pmu_lock);
		pmu_w32(pmu_r32(PWDCR(clk->module)) & ~clk->bits,
				PWDCR(clk->module));
		do {} while (--retry &&
			     (pmu_r32(PWDSR(clk->module)) & clk->bits));
		spin_unlock(&g_pmu_lock);
	}

	if (!retry)
		panic("activating PMU module failed!");

	return 0;
}