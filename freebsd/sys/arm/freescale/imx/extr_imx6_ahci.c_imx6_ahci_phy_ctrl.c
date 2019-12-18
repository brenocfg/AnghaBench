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
struct ahci_controller {int /*<<< orphan*/  r_mem; } ;

/* Variables and functions */
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SATA_P0PHYCR ; 
 int /*<<< orphan*/  SATA_P0PHYSR ; 
 int SATA_P0PHYSR_CR_ACK ; 

__attribute__((used)) static int
imx6_ahci_phy_ctrl(struct ahci_controller* sc, uint32_t bitmask, bool on)
{
	uint32_t v;
	int timeout;
	bool state;

	v = ATA_INL(sc->r_mem, SATA_P0PHYCR);
	if (on) {
		v |= bitmask;
	} else {
		v &= ~bitmask;
	}
	ATA_OUTL(sc->r_mem, SATA_P0PHYCR, v);

	for (timeout = 5000; timeout > 0; --timeout) {
		v = ATA_INL(sc->r_mem, SATA_P0PHYSR);
		state = (v & SATA_P0PHYSR_CR_ACK) == SATA_P0PHYSR_CR_ACK;
		if(state == on) {
			break;
		}
		DELAY(100);
	}

	if (timeout > 0) {
		return (0);
	}

	return (ETIMEDOUT);
}