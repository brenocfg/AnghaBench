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
struct mfi_softc {int (* mfi_read_fw_status ) (struct mfi_softc*) ;int mfi_flags; int /*<<< orphan*/  mfi_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int MFI_FLAGS_SKINNY ; 
 int MFI_FLAGS_TBOLT ; 
 int MFI_FWINIT_CLEAR_HANDSHAKE ; 
 int MFI_FWINIT_HOTPLUG ; 
 int MFI_FWINIT_READY ; 
#define  MFI_FWSTATE_BB_INIT 137 
#define  MFI_FWSTATE_BOOT_MESSAGE_PENDING 136 
#define  MFI_FWSTATE_DEVICE_SCAN 135 
#define  MFI_FWSTATE_FAULT 134 
#define  MFI_FWSTATE_FLUSH_CACHE 133 
#define  MFI_FWSTATE_FW_INIT 132 
#define  MFI_FWSTATE_FW_INIT_2 131 
 int MFI_FWSTATE_MASK ; 
#define  MFI_FWSTATE_OPERATIONAL 130 
 int MFI_FWSTATE_READY ; 
#define  MFI_FWSTATE_UNDEFINED 129 
#define  MFI_FWSTATE_WAIT_HANDSHAKE 128 
 int /*<<< orphan*/  MFI_IDB ; 
 int MFI_RESET_WAIT_TIME ; 
 int /*<<< orphan*/  MFI_SKINNY_IDB ; 
 int /*<<< orphan*/  MFI_WRITE4 (struct mfi_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int stub1 (struct mfi_softc*) ; 
 int stub2 (struct mfi_softc*) ; 

int
mfi_transition_firmware(struct mfi_softc *sc)
{
	uint32_t fw_state, cur_state;
	int max_wait, i;
	uint32_t cur_abs_reg_val = 0;
	uint32_t prev_abs_reg_val = 0;

	cur_abs_reg_val = sc->mfi_read_fw_status(sc);
	fw_state = cur_abs_reg_val & MFI_FWSTATE_MASK;
	while (fw_state != MFI_FWSTATE_READY) {
		if (bootverbose)
			device_printf(sc->mfi_dev, "Waiting for firmware to "
			"become ready\n");
		cur_state = fw_state;
		switch (fw_state) {
		case MFI_FWSTATE_FAULT:
			device_printf(sc->mfi_dev, "Firmware fault\n");
			return (ENXIO);
		case MFI_FWSTATE_WAIT_HANDSHAKE:
			if (sc->mfi_flags & MFI_FLAGS_SKINNY || sc->mfi_flags & MFI_FLAGS_TBOLT)
			    MFI_WRITE4(sc, MFI_SKINNY_IDB, MFI_FWINIT_CLEAR_HANDSHAKE);
			else
			    MFI_WRITE4(sc, MFI_IDB, MFI_FWINIT_CLEAR_HANDSHAKE);
			max_wait = MFI_RESET_WAIT_TIME;
			break;
		case MFI_FWSTATE_OPERATIONAL:
			if (sc->mfi_flags & MFI_FLAGS_SKINNY || sc->mfi_flags & MFI_FLAGS_TBOLT)
			    MFI_WRITE4(sc, MFI_SKINNY_IDB, 7);
			else
			    MFI_WRITE4(sc, MFI_IDB, MFI_FWINIT_READY);
			max_wait = MFI_RESET_WAIT_TIME;
			break;
		case MFI_FWSTATE_UNDEFINED:
		case MFI_FWSTATE_BB_INIT:
			max_wait = MFI_RESET_WAIT_TIME;
			break;
		case MFI_FWSTATE_FW_INIT_2:
			max_wait = MFI_RESET_WAIT_TIME;
			break;
		case MFI_FWSTATE_FW_INIT:
		case MFI_FWSTATE_FLUSH_CACHE:
			max_wait = MFI_RESET_WAIT_TIME;
			break;
		case MFI_FWSTATE_DEVICE_SCAN:
			max_wait = MFI_RESET_WAIT_TIME; /* wait for 180 seconds */
			prev_abs_reg_val = cur_abs_reg_val;
			break;
		case MFI_FWSTATE_BOOT_MESSAGE_PENDING:
			if (sc->mfi_flags & MFI_FLAGS_SKINNY || sc->mfi_flags & MFI_FLAGS_TBOLT)
			    MFI_WRITE4(sc, MFI_SKINNY_IDB, MFI_FWINIT_HOTPLUG);
			else
			    MFI_WRITE4(sc, MFI_IDB, MFI_FWINIT_HOTPLUG);
			max_wait = MFI_RESET_WAIT_TIME;
			break;
		default:
			device_printf(sc->mfi_dev, "Unknown firmware state %#x\n",
			    fw_state);
			return (ENXIO);
		}
		for (i = 0; i < (max_wait * 10); i++) {
			cur_abs_reg_val = sc->mfi_read_fw_status(sc);
			fw_state = cur_abs_reg_val & MFI_FWSTATE_MASK;
			if (fw_state == cur_state)
				DELAY(100000);
			else
				break;
		}
		if (fw_state == MFI_FWSTATE_DEVICE_SCAN) {
			/* Check the device scanning progress */
			if (prev_abs_reg_val != cur_abs_reg_val) {
				continue;
			}
		}
		if (fw_state == cur_state) {
			device_printf(sc->mfi_dev, "Firmware stuck in state "
			    "%#x\n", fw_state);
			return (ENXIO);
		}
	}
	return (0);
}