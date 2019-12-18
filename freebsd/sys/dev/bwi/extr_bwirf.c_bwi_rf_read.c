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
typedef  int uint16_t ;
struct bwi_softc {int dummy; } ;
struct bwi_rf {int rf_ctrl_rd; scalar_t__ rf_ctrl_adj; } ;
struct bwi_mac {struct bwi_softc* mac_sc; struct bwi_rf mac_rf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_RF_CTRL ; 
 int /*<<< orphan*/  BWI_RF_DATA_LO ; 
 int CSR_READ_2 (struct bwi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct bwi_softc*,int /*<<< orphan*/ ,int) ; 

uint16_t
bwi_rf_read(struct bwi_mac *mac, uint16_t ctrl)
{
	struct bwi_rf *rf = &mac->mac_rf;
	struct bwi_softc *sc = mac->mac_sc;

	ctrl |= rf->rf_ctrl_rd;
	if (rf->rf_ctrl_adj) {
		/* XXX */
		if (ctrl < 0x70)
			ctrl += 0x80;
		else if (ctrl < 0x80)
			ctrl += 0x70;
	}

	CSR_WRITE_2(sc, BWI_RF_CTRL, ctrl);
	return CSR_READ_2(sc, BWI_RF_DATA_LO);
}