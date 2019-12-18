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
struct ahci_channel {int /*<<< orphan*/  r_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHCI_P0DMACR ; 
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ahci_a10_ch_start(struct ahci_channel *ch)
{
	uint32_t reg;

	/*
	 * Magical values from Allwinner SDK, setup the DMA before start
	 * operations on this channel.
	 */
	reg = ATA_INL(ch->r_mem, AHCI_P0DMACR);
	reg &= ~0xff00;
	reg |= 0x4400;
	ATA_OUTL(ch->r_mem, AHCI_P0DMACR, reg);
}