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
struct bcm_sdhci_softc {int need_update_blk; int blksz_and_count; int cmd_and_mode; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int bus_size_t ;

/* Variables and functions */
 int RD4 (struct bcm_sdhci_softc*,int) ; 
 int SDHCI_BLOCK_COUNT ; 
 int SDHCI_BLOCK_SIZE ; 
 int SDHCI_COMMAND_FLAGS ; 
 int SDHCI_TRANSFER_MODE ; 
 int /*<<< orphan*/  WR4 (struct bcm_sdhci_softc*,int,int) ; 
 struct bcm_sdhci_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bcm_sdhci_write_2(device_t dev, struct sdhci_slot *slot, bus_size_t off, uint16_t val)
{
	struct bcm_sdhci_softc *sc = device_get_softc(dev);
	uint32_t val32;

	/*
	 * If we have a queued up 16bit value for blk size or count, use and
	 * update the saved value rather than doing any real register access.
	 * If we did not touch either since the last write, then read from
	 * register as at least block count can change.
	 * Similarly, if we are about to issue a command, always use the saved
	 * value for transfer mode as we can never write that without issuing
	 * a command.
	 */
	if ((off == SDHCI_BLOCK_SIZE || off == SDHCI_BLOCK_COUNT) &&
	    sc->need_update_blk)
		val32 = sc->blksz_and_count;
	else if (off == SDHCI_COMMAND_FLAGS)
		val32 = sc->cmd_and_mode;
	else
		val32 = RD4(sc, off & ~3);

	val32 &= ~(0xffff << (off & 3)*8);
	val32 |= (val << (off & 3)*8);

	if (off == SDHCI_TRANSFER_MODE)
		sc->cmd_and_mode = val32;
	else if (off == SDHCI_BLOCK_SIZE || off == SDHCI_BLOCK_COUNT) {
		sc->blksz_and_count = val32;
		sc->need_update_blk = true;
	} else {
		if (off == SDHCI_COMMAND_FLAGS) {
			/* If we saved blk writes, do them now before cmd. */
			if (sc->need_update_blk) {
				WR4(sc, SDHCI_BLOCK_SIZE, sc->blksz_and_count);
				sc->need_update_blk = false;
			}
			/* Always save cmd and mode registers. */
			sc->cmd_and_mode = val32;
		}
		WR4(sc, off & ~3, val32);
	}
}