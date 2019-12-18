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
typedef  int /*<<< orphan*/  uint32_t ;
struct bwi_softc {int /*<<< orphan*/  sc_dev; } ;
struct bwi_mac {int mac_rev; struct bwi_softc* mac_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_COMM_MOBJ ; 
 int /*<<< orphan*/  BWI_COMM_MOBJ_UCODE_STATE ; 
 int /*<<< orphan*/  BWI_MAC_STATUS ; 
 int /*<<< orphan*/  BWI_MAC_STATUS_HW_PS ; 
 int /*<<< orphan*/  BWI_MAC_STATUS_WAKEUP ; 
 scalar_t__ BWI_UCODE_STATE_PS ; 
 int /*<<< orphan*/  CSR_READ_4 (struct bwi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct bwi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ETIMEDOUT ; 
 scalar_t__ MOBJ_READ_2 (struct bwi_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NRETRY ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

int
bwi_mac_config_ps(struct bwi_mac *mac)
{
	struct bwi_softc *sc = mac->mac_sc;
	uint32_t status;

	status = CSR_READ_4(sc, BWI_MAC_STATUS);

	status &= ~BWI_MAC_STATUS_HW_PS;
	status |= BWI_MAC_STATUS_WAKEUP;
	CSR_WRITE_4(sc, BWI_MAC_STATUS, status);

	/* Flush pending bus write */
	CSR_READ_4(sc, BWI_MAC_STATUS);

	if (mac->mac_rev >= 5) {
		int i;

#define NRETRY	100
		for (i = 0; i < NRETRY; ++i) {
			if (MOBJ_READ_2(mac, BWI_COMM_MOBJ,
			    BWI_COMM_MOBJ_UCODE_STATE) != BWI_UCODE_STATE_PS)
				break;
			DELAY(10);
		}
		if (i == NRETRY) {
			device_printf(sc->sc_dev, "config PS failed\n");
			return ETIMEDOUT;
		}
#undef NRETRY
	}
	return 0;
}