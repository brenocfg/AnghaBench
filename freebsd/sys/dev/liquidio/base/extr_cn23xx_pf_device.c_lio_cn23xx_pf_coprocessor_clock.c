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
typedef  int uint32_t ;
struct octeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIO_CN23XX_RST_BOOT ; 
 int lio_pci_readq (struct octeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
lio_cn23xx_pf_coprocessor_clock(struct octeon_device *oct)
{
	/*
	 * Bits 29:24 of RST_BOOT[PNR_MUL] holds the ref.clock MULTIPLIER
	 * for SLI.
	 */

	/* TBD: get the info in Hand-shake */
	return (((lio_pci_readq(oct, LIO_CN23XX_RST_BOOT) >> 24) & 0x3f) * 50);
}