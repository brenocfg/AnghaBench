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

/* Variables and functions */
 unsigned long HV_EOK ; 
 int /*<<< orphan*/  HV_N2_PERF_SPARC_CTL ; 
 int PCR_N2_HTRACE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  direct_pcr_write (unsigned long,int) ; 
 unsigned long sun4v_niagara2_setperf (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void n2_pcr_write(unsigned long reg_num, u64 val)
{
	unsigned long ret;

	WARN_ON_ONCE(reg_num != 0);
	if (val & PCR_N2_HTRACE) {
		ret = sun4v_niagara2_setperf(HV_N2_PERF_SPARC_CTL, val);
		if (ret != HV_EOK)
			direct_pcr_write(reg_num, val);
	} else
		direct_pcr_write(reg_num, val);
}