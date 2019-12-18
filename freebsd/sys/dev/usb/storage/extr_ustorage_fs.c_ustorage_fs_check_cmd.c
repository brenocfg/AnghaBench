#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  unsigned long uint16_t ;
struct TYPE_5__ {scalar_t__ cmd_len; scalar_t__ lun; struct ustorage_fs_lun* currlun; } ;
struct ustorage_fs_softc {scalar_t__ sc_last_lun; TYPE_3__* sc_cbw; TYPE_2__ sc_transfer; struct ustorage_fs_lun* sc_lun; TYPE_1__* sc_csw; } ;
struct ustorage_fs_lun {scalar_t__ sense_data; scalar_t__ unit_attention_data; int /*<<< orphan*/  memory_image; scalar_t__ info_valid; scalar_t__ sense_data_info; } ;
struct TYPE_6__ {int* CBWCDB; } ;
struct TYPE_4__ {int /*<<< orphan*/  bCSWStatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSWSTATUS_PHASE ; 
 int /*<<< orphan*/  DPRINTF (char*,scalar_t__,scalar_t__) ; 
 int SC_INQUIRY ; 
 int SC_REQUEST_SENSE ; 
 scalar_t__ SS_INVALID_FIELD_IN_CDB ; 
 scalar_t__ SS_MEDIUM_NOT_PRESENT ; 
 scalar_t__ SS_NO_SENSE ; 

__attribute__((used)) static uint8_t
ustorage_fs_check_cmd(struct ustorage_fs_softc *sc, uint8_t min_cmd_size,
    uint16_t mask, uint8_t needs_medium)
{
	struct ustorage_fs_lun *currlun;
	uint8_t lun = (sc->sc_cbw->CBWCDB[1] >> 5);
	uint8_t i;

	/* Verify the length of the command itself */
	if (min_cmd_size > sc->sc_transfer.cmd_len) {
		DPRINTF("%u > %u\n",
		    min_cmd_size, sc->sc_transfer.cmd_len);
		sc->sc_csw->bCSWStatus = CSWSTATUS_PHASE;
		return (1);
	}
	/* Mask away the LUN */
	sc->sc_cbw->CBWCDB[1] &= 0x1f;

	/* Check if LUN is correct */
	if (lun != sc->sc_transfer.lun) {

	}
	/* Check the LUN */
	if (sc->sc_transfer.lun <= sc->sc_last_lun) {
		sc->sc_transfer.currlun = currlun =
		    sc->sc_lun + sc->sc_transfer.lun;
		if (sc->sc_cbw->CBWCDB[0] != SC_REQUEST_SENSE) {
			currlun->sense_data = SS_NO_SENSE;
			currlun->sense_data_info = 0;
			currlun->info_valid = 0;
		}
		/*
		 * If a unit attention condition exists, only INQUIRY
		 * and REQUEST SENSE commands are allowed. Anything
		 * else must fail!
		 */
		if ((currlun->unit_attention_data != SS_NO_SENSE) &&
		    (sc->sc_cbw->CBWCDB[0] != SC_INQUIRY) &&
		    (sc->sc_cbw->CBWCDB[0] != SC_REQUEST_SENSE)) {
			currlun->sense_data = currlun->unit_attention_data;
			currlun->unit_attention_data = SS_NO_SENSE;
			return (1);
		}
	} else {
		sc->sc_transfer.currlun = currlun = NULL;

		/*
		 * INQUIRY and REQUEST SENSE commands are explicitly allowed
		 * to use unsupported LUNs; all others may not.
		 */
		if ((sc->sc_cbw->CBWCDB[0] != SC_INQUIRY) &&
		    (sc->sc_cbw->CBWCDB[0] != SC_REQUEST_SENSE)) {
			return (1);
		}
	}

	/*
	 * Check that only command bytes listed in the mask are
	 * non-zero.
	 */
	for (i = 0; i != min_cmd_size; i++) {
		if (sc->sc_cbw->CBWCDB[i] && !(mask & (1UL << i))) {
			if (currlun) {
				currlun->sense_data = SS_INVALID_FIELD_IN_CDB;
			}
			return (1);
		}
	}

	/*
	 * If the medium isn't mounted and the command needs to access
	 * it, return an error.
	 */
	if (currlun && (!currlun->memory_image) && needs_medium) {
		currlun->sense_data = SS_MEDIUM_NOT_PRESENT;
		return (1);
	}
	return (0);
}