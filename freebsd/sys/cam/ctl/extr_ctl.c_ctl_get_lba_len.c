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
struct TYPE_4__ {int* cdb; } ;
struct TYPE_3__ {scalar_t__ io_type; } ;
union ctl_io {TYPE_2__ scsiio; TYPE_1__ io_hdr; } ;
typedef  int uint64_t ;
struct scsi_write_verify_16 {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct scsi_write_verify_12 {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct scsi_write_verify_10 {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct scsi_write_same_16 {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct scsi_write_same_10 {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct scsi_write_atomic_16 {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct scsi_verify_16 {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct scsi_verify_12 {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct scsi_verify_10 {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct scsi_rw_6 {int length; int /*<<< orphan*/  addr; } ;
struct scsi_rw_16 {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct scsi_rw_12 {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct scsi_rw_10 {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct scsi_get_lba_status {int /*<<< orphan*/  addr; } ;
struct scsi_compare_and_write {int length; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
#define  COMPARE_AND_WRITE 147 
 scalar_t__ CTL_IO_SCSI ; 
#define  READ_10 146 
#define  READ_12 145 
#define  READ_16 144 
#define  READ_6 143 
#define  SERVICE_ACTION_IN 142 
 int UINT32_MAX ; 
 int UINT64_MAX ; 
#define  UNMAP 141 
#define  VERIFY_10 140 
#define  VERIFY_12 139 
#define  VERIFY_16 138 
#define  WRITE_10 137 
#define  WRITE_12 136 
#define  WRITE_16 135 
#define  WRITE_6 134 
#define  WRITE_ATOMIC_16 133 
#define  WRITE_SAME_10 132 
#define  WRITE_SAME_16 131 
#define  WRITE_VERIFY_10 130 
#define  WRITE_VERIFY_12 129 
#define  WRITE_VERIFY_16 128 
 int scsi_2btoul (int /*<<< orphan*/ ) ; 
 int scsi_3btoul (int /*<<< orphan*/ ) ; 
 int scsi_4btoul (int /*<<< orphan*/ ) ; 
 int scsi_8btou64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ctl_get_lba_len(union ctl_io *io, uint64_t *lba, uint64_t *len)
{
	if (io->io_hdr.io_type != CTL_IO_SCSI)
		return (1);

	switch (io->scsiio.cdb[0]) {
	case COMPARE_AND_WRITE: {
		struct scsi_compare_and_write *cdb;

		cdb = (struct scsi_compare_and_write *)io->scsiio.cdb;

		*lba = scsi_8btou64(cdb->addr);
		*len = cdb->length;
		break;
	}
	case READ_6:
	case WRITE_6: {
		struct scsi_rw_6 *cdb;

		cdb = (struct scsi_rw_6 *)io->scsiio.cdb;

		*lba = scsi_3btoul(cdb->addr);
		/* only 5 bits are valid in the most significant address byte */
		*lba &= 0x1fffff;
		*len = cdb->length;
		break;
	}
	case READ_10:
	case WRITE_10: {
		struct scsi_rw_10 *cdb;

		cdb = (struct scsi_rw_10 *)io->scsiio.cdb;

		*lba = scsi_4btoul(cdb->addr);
		*len = scsi_2btoul(cdb->length);
		break;
	}
	case WRITE_VERIFY_10: {
		struct scsi_write_verify_10 *cdb;

		cdb = (struct scsi_write_verify_10 *)io->scsiio.cdb;

		*lba = scsi_4btoul(cdb->addr);
		*len = scsi_2btoul(cdb->length);
		break;
	}
	case READ_12:
	case WRITE_12: {
		struct scsi_rw_12 *cdb;

		cdb = (struct scsi_rw_12 *)io->scsiio.cdb;

		*lba = scsi_4btoul(cdb->addr);
		*len = scsi_4btoul(cdb->length);
		break;
	}
	case WRITE_VERIFY_12: {
		struct scsi_write_verify_12 *cdb;

		cdb = (struct scsi_write_verify_12 *)io->scsiio.cdb;

		*lba = scsi_4btoul(cdb->addr);
		*len = scsi_4btoul(cdb->length);
		break;
	}
	case READ_16:
	case WRITE_16: {
		struct scsi_rw_16 *cdb;

		cdb = (struct scsi_rw_16 *)io->scsiio.cdb;

		*lba = scsi_8btou64(cdb->addr);
		*len = scsi_4btoul(cdb->length);
		break;
	}
	case WRITE_ATOMIC_16: {
		struct scsi_write_atomic_16 *cdb;

		cdb = (struct scsi_write_atomic_16 *)io->scsiio.cdb;

		*lba = scsi_8btou64(cdb->addr);
		*len = scsi_2btoul(cdb->length);
		break;
	}
	case WRITE_VERIFY_16: {
		struct scsi_write_verify_16 *cdb;

		cdb = (struct scsi_write_verify_16 *)io->scsiio.cdb;

		*lba = scsi_8btou64(cdb->addr);
		*len = scsi_4btoul(cdb->length);
		break;
	}
	case WRITE_SAME_10: {
		struct scsi_write_same_10 *cdb;

		cdb = (struct scsi_write_same_10 *)io->scsiio.cdb;

		*lba = scsi_4btoul(cdb->addr);
		*len = scsi_2btoul(cdb->length);
		break;
	}
	case WRITE_SAME_16: {
		struct scsi_write_same_16 *cdb;

		cdb = (struct scsi_write_same_16 *)io->scsiio.cdb;

		*lba = scsi_8btou64(cdb->addr);
		*len = scsi_4btoul(cdb->length);
		break;
	}
	case VERIFY_10: {
		struct scsi_verify_10 *cdb;

		cdb = (struct scsi_verify_10 *)io->scsiio.cdb;

		*lba = scsi_4btoul(cdb->addr);
		*len = scsi_2btoul(cdb->length);
		break;
	}
	case VERIFY_12: {
		struct scsi_verify_12 *cdb;

		cdb = (struct scsi_verify_12 *)io->scsiio.cdb;

		*lba = scsi_4btoul(cdb->addr);
		*len = scsi_4btoul(cdb->length);
		break;
	}
	case VERIFY_16: {
		struct scsi_verify_16 *cdb;

		cdb = (struct scsi_verify_16 *)io->scsiio.cdb;

		*lba = scsi_8btou64(cdb->addr);
		*len = scsi_4btoul(cdb->length);
		break;
	}
	case UNMAP: {
		*lba = 0;
		*len = UINT64_MAX;
		break;
	}
	case SERVICE_ACTION_IN: {	/* GET LBA STATUS */
		struct scsi_get_lba_status *cdb;

		cdb = (struct scsi_get_lba_status *)io->scsiio.cdb;
		*lba = scsi_8btou64(cdb->addr);
		*len = UINT32_MAX;
		break;
	}
	default:
		return (1);
		break; /* NOTREACHED */
	}

	return (0);
}