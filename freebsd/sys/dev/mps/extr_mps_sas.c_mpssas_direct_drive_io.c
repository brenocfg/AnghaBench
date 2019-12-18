#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct mpssas_softc {struct mps_softc* sc; } ;
struct mps_softc {scalar_t__ DD_dev_handle; int DD_block_exponent; int DD_max_lba; int DD_stripe_size; int DD_stripe_exponent; int DD_num_phys_disks; TYPE_1__* DD_column_map; } ;
struct TYPE_7__ {scalar_t__ DevHandle; } ;
struct TYPE_8__ {TYPE_2__ SCSIIO; } ;
struct mps_command {int cm_length; int /*<<< orphan*/  cm_flags; TYPE_3__ cm_desc; scalar_t__ cm_req; } ;
typedef  TYPE_5__* pMpi2SCSIIORequest_t ;
struct TYPE_9__ {int* CDB32; } ;
struct TYPE_10__ {scalar_t__ DevHandle; TYPE_4__ CDB; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPS_CM_FLAGS_DD_IO ; 
 int READ_10 ; 
 int READ_12 ; 
 int READ_16 ; 
 int READ_6 ; 
 int WRITE_10 ; 
 int WRITE_12 ; 
 int WRITE_16 ; 
 int WRITE_6 ; 
 void* htole16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mpssas_direct_drive_io(struct mpssas_softc *sassc, struct mps_command *cm,
    union ccb *ccb) {
	pMpi2SCSIIORequest_t	pIO_req;
	struct mps_softc	*sc = sassc->sc;
	uint64_t		virtLBA;
	uint32_t		physLBA, stripe_offset, stripe_unit;
	uint32_t		io_size, column;
	uint8_t			*ptrLBA, lba_idx, physLBA_byte, *CDB;

	/*
	 * If this is a valid SCSI command (Read6, Read10, Read16, Write6,
	 * Write10, or Write16), build a direct I/O message.  Otherwise, the I/O
	 * will be sent to the IR volume itself.  Since Read6 and Write6 are a
	 * bit different than the 10/16 CDBs, handle them separately.
	 */
	pIO_req = (pMpi2SCSIIORequest_t)cm->cm_req;
	CDB = pIO_req->CDB.CDB32;

	/*
	 * Handle 6 byte CDBs.
	 */
	if ((pIO_req->DevHandle == sc->DD_dev_handle) && ((CDB[0] == READ_6) ||
	    (CDB[0] == WRITE_6))) {
		/*
		 * Get the transfer size in blocks.
		 */
		io_size = (cm->cm_length >> sc->DD_block_exponent);

		/*
		 * Get virtual LBA given in the CDB.
		 */
		virtLBA = ((uint64_t)(CDB[1] & 0x1F) << 16) |
		    ((uint64_t)CDB[2] << 8) | (uint64_t)CDB[3];

		/*
		 * Check that LBA range for I/O does not exceed volume's
		 * MaxLBA.
		 */
		if ((virtLBA + (uint64_t)io_size - 1) <=
		    sc->DD_max_lba) {
			/*
			 * Check if the I/O crosses a stripe boundary.  If not,
			 * translate the virtual LBA to a physical LBA and set
			 * the DevHandle for the PhysDisk to be used.  If it
			 * does cross a boundary, do normal I/O.  To get the
			 * right DevHandle to use, get the map number for the
			 * column, then use that map number to look up the
			 * DevHandle of the PhysDisk.
			 */
			stripe_offset = (uint32_t)virtLBA &
			    (sc->DD_stripe_size - 1);
			if ((stripe_offset + io_size) <= sc->DD_stripe_size) {
				physLBA = (uint32_t)virtLBA >>
				    sc->DD_stripe_exponent;
				stripe_unit = physLBA / sc->DD_num_phys_disks;
				column = physLBA % sc->DD_num_phys_disks;
				pIO_req->DevHandle =
				    htole16(sc->DD_column_map[column].dev_handle);
				/* ???? Is this endian safe*/
				cm->cm_desc.SCSIIO.DevHandle =
				    pIO_req->DevHandle;

				physLBA = (stripe_unit <<
				    sc->DD_stripe_exponent) + stripe_offset;
				ptrLBA = &pIO_req->CDB.CDB32[1];
				physLBA_byte = (uint8_t)(physLBA >> 16);
				*ptrLBA = physLBA_byte;
				ptrLBA = &pIO_req->CDB.CDB32[2];
				physLBA_byte = (uint8_t)(physLBA >> 8);
				*ptrLBA = physLBA_byte;
				ptrLBA = &pIO_req->CDB.CDB32[3];
				physLBA_byte = (uint8_t)physLBA;
				*ptrLBA = physLBA_byte;

				/*
				 * Set flag that Direct Drive I/O is
				 * being done.
				 */
				cm->cm_flags |= MPS_CM_FLAGS_DD_IO;
			}
		}
		return;
	}

	/*
	 * Handle 10, 12 or 16 byte CDBs.
	 */
	if ((pIO_req->DevHandle == sc->DD_dev_handle) && ((CDB[0] == READ_10) ||
	    (CDB[0] == WRITE_10) || (CDB[0] == READ_16) ||
	    (CDB[0] == WRITE_16) || (CDB[0] == READ_12) ||
	    (CDB[0] == WRITE_12))) {
		/*
		 * For 16-byte CDB's, verify that the upper 4 bytes of the CDB
		 * are 0.  If not, this is accessing beyond 2TB so handle it in
		 * the else section.  10-byte and 12-byte CDB's are OK.
		 * FreeBSD sends very rare 12 byte READ/WRITE, but driver is 
		 * ready to accept 12byte CDB for Direct IOs.
		 */
		if ((CDB[0] == READ_10 || CDB[0] == WRITE_10) ||
		    (CDB[0] == READ_12 || CDB[0] == WRITE_12) ||
		    !(CDB[2] | CDB[3] | CDB[4] | CDB[5])) {
			/*
			 * Get the transfer size in blocks.
			 */
			io_size = (cm->cm_length >> sc->DD_block_exponent);

			/*
			 * Get virtual LBA.  Point to correct lower 4 bytes of
			 * LBA in the CDB depending on command.
			 */
			lba_idx = ((CDB[0] == READ_12) || 
				(CDB[0] == WRITE_12) ||
				(CDB[0] == READ_10) ||
				(CDB[0] == WRITE_10))? 2 : 6;
			virtLBA = ((uint64_t)CDB[lba_idx] << 24) |
			    ((uint64_t)CDB[lba_idx + 1] << 16) |
			    ((uint64_t)CDB[lba_idx + 2] << 8) |
			    (uint64_t)CDB[lba_idx + 3];

			/*
			 * Check that LBA range for I/O does not exceed volume's
			 * MaxLBA.
			 */
			if ((virtLBA + (uint64_t)io_size - 1) <=
			    sc->DD_max_lba) {
				/*
				 * Check if the I/O crosses a stripe boundary.
				 * If not, translate the virtual LBA to a
				 * physical LBA and set the DevHandle for the
				 * PhysDisk to be used.  If it does cross a
				 * boundary, do normal I/O.  To get the right
				 * DevHandle to use, get the map number for the
				 * column, then use that map number to look up
				 * the DevHandle of the PhysDisk.
				 */
				stripe_offset = (uint32_t)virtLBA &
				    (sc->DD_stripe_size - 1);
				if ((stripe_offset + io_size) <=
				    sc->DD_stripe_size) {
					physLBA = (uint32_t)virtLBA >>
					    sc->DD_stripe_exponent;
					stripe_unit = physLBA /
					    sc->DD_num_phys_disks;
					column = physLBA %
					    sc->DD_num_phys_disks;
					pIO_req->DevHandle =
					    htole16(sc->DD_column_map[column].
					    dev_handle);
					cm->cm_desc.SCSIIO.DevHandle =
					    pIO_req->DevHandle;

					physLBA = (stripe_unit <<
					    sc->DD_stripe_exponent) +
					    stripe_offset;
					ptrLBA =
					    &pIO_req->CDB.CDB32[lba_idx];
					physLBA_byte = (uint8_t)(physLBA >> 24);
					*ptrLBA = physLBA_byte;
					ptrLBA =
					    &pIO_req->CDB.CDB32[lba_idx + 1];
					physLBA_byte = (uint8_t)(physLBA >> 16);
					*ptrLBA = physLBA_byte;
					ptrLBA =
					    &pIO_req->CDB.CDB32[lba_idx + 2];
					physLBA_byte = (uint8_t)(physLBA >> 8);
					*ptrLBA = physLBA_byte;
					ptrLBA =
					    &pIO_req->CDB.CDB32[lba_idx + 3];
					physLBA_byte = (uint8_t)physLBA;
					*ptrLBA = physLBA_byte;

					/*
					 * Set flag that Direct Drive I/O is
					 * being done.
					 */
					cm->cm_flags |= MPS_CM_FLAGS_DD_IO;
				}
			}
		} else {
			/*
			 * 16-byte CDB and the upper 4 bytes of the CDB are not
			 * 0.  Get the transfer size in blocks.
			 */
			io_size = (cm->cm_length >> sc->DD_block_exponent);

			/*
			 * Get virtual LBA.
			 */
			virtLBA = ((uint64_t)CDB[2] << 54) |
			    ((uint64_t)CDB[3] << 48) |
			    ((uint64_t)CDB[4] << 40) |
			    ((uint64_t)CDB[5] << 32) |
			    ((uint64_t)CDB[6] << 24) |
			    ((uint64_t)CDB[7] << 16) |
			    ((uint64_t)CDB[8] << 8) |
			    (uint64_t)CDB[9]; 

			/*
			 * Check that LBA range for I/O does not exceed volume's
			 * MaxLBA.
			 */
			if ((virtLBA + (uint64_t)io_size - 1) <=
			    sc->DD_max_lba) {
				/*
				 * Check if the I/O crosses a stripe boundary.
				 * If not, translate the virtual LBA to a
				 * physical LBA and set the DevHandle for the
				 * PhysDisk to be used.  If it does cross a
				 * boundary, do normal I/O.  To get the right
				 * DevHandle to use, get the map number for the
				 * column, then use that map number to look up
				 * the DevHandle of the PhysDisk.
				 */
				stripe_offset = (uint32_t)virtLBA &
				    (sc->DD_stripe_size - 1);
				if ((stripe_offset + io_size) <=
				    sc->DD_stripe_size) {
					physLBA = (uint32_t)(virtLBA >>
					    sc->DD_stripe_exponent);
					stripe_unit = physLBA /
					    sc->DD_num_phys_disks;
					column = physLBA %
					    sc->DD_num_phys_disks;
					pIO_req->DevHandle =
					    htole16(sc->DD_column_map[column].
					    dev_handle);
					cm->cm_desc.SCSIIO.DevHandle =
					    pIO_req->DevHandle;

					physLBA = (stripe_unit <<
					    sc->DD_stripe_exponent) +
					    stripe_offset;

					/*
					 * Set upper 4 bytes of LBA to 0.  We
					 * assume that the phys disks are less
					 * than 2 TB's in size.  Then, set the
					 * lower 4 bytes.
					 */
					pIO_req->CDB.CDB32[2] = 0;
					pIO_req->CDB.CDB32[3] = 0;
					pIO_req->CDB.CDB32[4] = 0;
					pIO_req->CDB.CDB32[5] = 0;
					ptrLBA = &pIO_req->CDB.CDB32[6];
					physLBA_byte = (uint8_t)(physLBA >> 24);
					*ptrLBA = physLBA_byte;
					ptrLBA = &pIO_req->CDB.CDB32[7];
					physLBA_byte = (uint8_t)(physLBA >> 16);
					*ptrLBA = physLBA_byte;
					ptrLBA = &pIO_req->CDB.CDB32[8];
					physLBA_byte = (uint8_t)(physLBA >> 8);
					*ptrLBA = physLBA_byte;
					ptrLBA = &pIO_req->CDB.CDB32[9];
					physLBA_byte = (uint8_t)physLBA;
					*ptrLBA = physLBA_byte;

					/*
					 * Set flag that Direct Drive I/O is
					 * being done.
					 */
					cm->cm_flags |= MPS_CM_FLAGS_DD_IO;
				}
			}
		}
	}
}