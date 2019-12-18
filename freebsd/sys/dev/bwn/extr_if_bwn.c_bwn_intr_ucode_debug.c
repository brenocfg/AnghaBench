#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct bwn_softc {int /*<<< orphan*/  sc_dev; } ;
struct TYPE_2__ {scalar_t__ opensource; } ;
struct bwn_mac {TYPE_1__ mac_fw; struct bwn_softc* mac_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_DEBUGINTR_ACK ; 
#define  BWN_DEBUGINTR_DUMP_REGS 131 
#define  BWN_DEBUGINTR_DUMP_SHM 130 
#define  BWN_DEBUGINTR_MARKER 129 
#define  BWN_DEBUGINTR_PANIC 128 
 int /*<<< orphan*/  BWN_DEBUGINTR_REASON_REG ; 
 int /*<<< orphan*/  BWN_SCRATCH ; 
 int /*<<< orphan*/  bwn_handle_fwpanic (struct bwn_mac*) ; 
 int bwn_shm_read_2 (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_shm_write_2 (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
bwn_intr_ucode_debug(struct bwn_mac *mac)
{
	struct bwn_softc *sc = mac->mac_sc;
	uint16_t reason;

	if (mac->mac_fw.opensource == 0)
		return;

	reason = bwn_shm_read_2(mac, BWN_SCRATCH, BWN_DEBUGINTR_REASON_REG);
	switch (reason) {
	case BWN_DEBUGINTR_PANIC:
		bwn_handle_fwpanic(mac);
		break;
	case BWN_DEBUGINTR_DUMP_SHM:
		device_printf(sc->sc_dev, "BWN_DEBUGINTR_DUMP_SHM\n");
		break;
	case BWN_DEBUGINTR_DUMP_REGS:
		device_printf(sc->sc_dev, "BWN_DEBUGINTR_DUMP_REGS\n");
		break;
	case BWN_DEBUGINTR_MARKER:
		device_printf(sc->sc_dev, "BWN_DEBUGINTR_MARKER\n");
		break;
	default:
		device_printf(sc->sc_dev,
		    "ucode debug unknown reason: %#x\n", reason);
	}

	bwn_shm_write_2(mac, BWN_SCRATCH, BWN_DEBUGINTR_REASON_REG,
	    BWN_DEBUGINTR_ACK);
}