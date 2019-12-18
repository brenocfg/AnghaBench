#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int data_rem; scalar_t__ data_ptr; struct ustorage_fs_lun* currlun; } ;
struct ustorage_fs_softc {TYPE_2__ sc_transfer; TYPE_1__* sc_cbw; } ;
struct ustorage_fs_lun {int num_sectors; scalar_t__ memory_image; int /*<<< orphan*/  sense_data; scalar_t__ read_only; } ;
struct TYPE_3__ {int* CBWCDB; } ;

/* Variables and functions */
 int SC_WRITE_6 ; 
 int /*<<< orphan*/  SS_INVALID_FIELD_IN_CDB ; 
 int /*<<< orphan*/  SS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE ; 
 int /*<<< orphan*/  SS_WRITE_PROTECTED ; 
 int get_be16 (int*) ; 
 int get_be32 (int*) ; 

__attribute__((used)) static uint8_t
ustorage_fs_write(struct ustorage_fs_softc *sc)
{
	struct ustorage_fs_lun *currlun = sc->sc_transfer.currlun;
	uint64_t file_offset;
	uint32_t lba;
	uint32_t len;

	if (currlun->read_only) {
		currlun->sense_data = SS_WRITE_PROTECTED;
		return (1);
	}
	/* XXX clear SYNC */

	/*
	 * Get the starting Logical Block Address and check that it's not
	 * too big.
	 */
	if (sc->sc_cbw->CBWCDB[0] == SC_WRITE_6)
		lba = (((uint32_t)sc->sc_cbw->CBWCDB[1]) << 16) |
		    get_be16(&sc->sc_cbw->CBWCDB[2]);
	else {
		lba = get_be32(&sc->sc_cbw->CBWCDB[2]);

		/*
		 * We allow DPO (Disable Page Out = don't save data in the
		 * cache) and FUA (Force Unit Access = write directly to the
		 * medium).  We don't implement DPO; we implement FUA by
		 * performing synchronous output.
		 */
		if ((sc->sc_cbw->CBWCDB[1] & ~0x18) != 0) {
			currlun->sense_data = SS_INVALID_FIELD_IN_CDB;
			return (1);
		}
		if (sc->sc_cbw->CBWCDB[1] & 0x08) {
			/* FUA */
			/* XXX set SYNC flag here */
		}
	}

	len = sc->sc_transfer.data_rem >> 9;
	len += lba;

	if ((len < lba) ||
	    (len > currlun->num_sectors) ||
	    (lba >= currlun->num_sectors)) {
		currlun->sense_data = SS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE;
		return (1);
	}
	file_offset = lba;
	file_offset <<= 9;

	sc->sc_transfer.data_ptr = currlun->memory_image + file_offset;

	return (0);
}