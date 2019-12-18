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
 int /*<<< orphan*/  AR71XX_CPU_DDR_FLUSH_WMAC ; 
 int /*<<< orphan*/  ar71xx_device_flush_ddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_intr (void*) ; 

__attribute__((used)) static void
ath_ahb_intr(void *arg)
{
	/* XXX TODO: check if its ours! */
	ar71xx_device_flush_ddr(AR71XX_CPU_DDR_FLUSH_WMAC);
	ath_intr(arg);
}