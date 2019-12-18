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
 int /*<<< orphan*/  S3C2412_PWRCFG ; 
 unsigned long S3C2412_PWRCFG_STANDBYWFI_SLEEP ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  s3c2412_sleep_enter () ; 

__attribute__((used)) static int s3c2412_cpu_suspend(unsigned long arg)
{
	unsigned long tmp;

	/* set our standby method to sleep */

	tmp = __raw_readl(S3C2412_PWRCFG);
	tmp |= S3C2412_PWRCFG_STANDBYWFI_SLEEP;
	__raw_writel(tmp, S3C2412_PWRCFG);

	s3c2412_sleep_enter();

	pr_info("Failed to suspend the system\n");
	return 1; /* Aborting suspend */
}