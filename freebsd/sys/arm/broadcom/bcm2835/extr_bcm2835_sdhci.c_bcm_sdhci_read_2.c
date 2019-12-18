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
typedef  int uint16_t ;
struct sdhci_slot {int dummy; } ;
struct bcm_sdhci_softc {int blksz_and_count; int cmd_and_mode; scalar_t__ need_update_blk; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int bus_size_t ;

/* Variables and functions */
 int RD4 (struct bcm_sdhci_softc*,int) ; 
 int SDHCI_BLOCK_COUNT ; 
 int SDHCI_BLOCK_SIZE ; 
 int SDHCI_COMMAND_FLAGS ; 
 int SDHCI_TRANSFER_MODE ; 
 struct bcm_sdhci_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint16_t
bcm_sdhci_read_2(device_t dev, struct sdhci_slot *slot, bus_size_t off)
{
	struct bcm_sdhci_softc *sc = device_get_softc(dev);
	uint32_t val32;

	/*
	 * Standard 32-bit handling of command and transfer mode, as
	 * well as block size and count.
	 */
	if ((off == SDHCI_BLOCK_SIZE || off == SDHCI_BLOCK_COUNT) &&
	    sc->need_update_blk)
		val32 = sc->blksz_and_count;
	else if (off == SDHCI_TRANSFER_MODE || off == SDHCI_COMMAND_FLAGS)
		val32 = sc->cmd_and_mode;
	else
		val32 = RD4(sc, off & ~3);

	return ((val32 >> (off & 3)*8) & 0xffff);
}