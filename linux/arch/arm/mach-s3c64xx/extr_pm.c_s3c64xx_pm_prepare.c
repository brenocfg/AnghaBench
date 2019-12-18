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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S3C64XX_INFORM0 ; 
 int /*<<< orphan*/  S3C64XX_PWR_CFG ; 
 int /*<<< orphan*/  S3C64XX_WAKEUP_STAT ; 
 int /*<<< orphan*/  __pa_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_cpu_resume ; 
 int /*<<< orphan*/  samsung_sync_wakemask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_irqs ; 

__attribute__((used)) static void s3c64xx_pm_prepare(void)
{
	samsung_sync_wakemask(S3C64XX_PWR_CFG,
			      wake_irqs, ARRAY_SIZE(wake_irqs));

	/* store address of resume. */
	__raw_writel(__pa_symbol(s3c_cpu_resume), S3C64XX_INFORM0);

	/* ensure previous wakeup state is cleared before sleeping */
	__raw_writel(__raw_readl(S3C64XX_WAKEUP_STAT), S3C64XX_WAKEUP_STAT);
}