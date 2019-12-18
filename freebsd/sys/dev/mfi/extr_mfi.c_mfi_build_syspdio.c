#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union mfi_frame {int dummy; } mfi_frame ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  void* uint32_t ;
struct mfi_softc {int /*<<< orphan*/  mfi_io_lock; } ;
struct TYPE_6__ {uintptr_t target_id; int /*<<< orphan*/  cdb_len; int /*<<< orphan*/  data_len; int /*<<< orphan*/  sense_len; scalar_t__ scsi_status; int /*<<< orphan*/  flags; scalar_t__ timeout; scalar_t__ lun_id; int /*<<< orphan*/  cmd; } ;
struct mfi_pass_frame {int /*<<< orphan*/  sgl; void* sense_addr_hi; void* sense_addr_lo; TYPE_2__ header; TYPE_3__* cdb; } ;
struct mfi_command {int cm_flags; int /*<<< orphan*/  cm_total_frame_size; int /*<<< orphan*/ * cm_sg; int /*<<< orphan*/  cm_len; int /*<<< orphan*/  cm_data; struct bio* cm_private; int /*<<< orphan*/  cm_complete; scalar_t__ cm_sense_busaddr; TYPE_3__* cm_frame; } ;
struct bio {int bio_cmd; int /*<<< orphan*/  bio_bcount; scalar_t__ bio_driver1; int /*<<< orphan*/  bio_pblkno; } ;
struct TYPE_5__ {void* context; } ;
struct TYPE_7__ {struct mfi_pass_frame pass; TYPE_1__ header; } ;

/* Variables and functions */
#define  BIO_READ 129 
#define  BIO_WRITE 128 
 int /*<<< orphan*/  MA_OWNED ; 
 int MFI_CMD_BIO ; 
 int MFI_CMD_DATAIN ; 
 int MFI_CMD_DATAOUT ; 
 int /*<<< orphan*/  MFI_CMD_PD_SCSI_IO ; 
 int /*<<< orphan*/  MFI_PASS_FRAME_SIZE ; 
 int /*<<< orphan*/  MFI_SECTOR_LEN ; 
 int /*<<< orphan*/  MFI_SENSE_LEN ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 int howmany (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfi_bio_complete ; 
 int /*<<< orphan*/  mfi_build_cdb (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 struct mfi_command* mfi_dequeue_free (struct mfi_softc*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  unmapped_buf ; 

__attribute__((used)) static struct mfi_command *
mfi_build_syspdio(struct mfi_softc *sc, struct bio *bio)
{
	struct mfi_command *cm;
	struct mfi_pass_frame *pass;
	uint32_t context = 0;
	int flags = 0, blkcount = 0, readop;
	uint8_t cdb_len;

	mtx_assert(&sc->mfi_io_lock, MA_OWNED);

	if ((cm = mfi_dequeue_free(sc)) == NULL)
	    return (NULL);

	/* Zero out the MFI frame */
	context = cm->cm_frame->header.context;
	bzero(cm->cm_frame, sizeof(union mfi_frame));
	cm->cm_frame->header.context = context;
	pass = &cm->cm_frame->pass;
	bzero(pass->cdb, 16);
	pass->header.cmd = MFI_CMD_PD_SCSI_IO;
	switch (bio->bio_cmd) {
	case BIO_READ:
		flags = MFI_CMD_DATAIN | MFI_CMD_BIO;
		readop = 1;
		break;
	case BIO_WRITE:
		flags = MFI_CMD_DATAOUT | MFI_CMD_BIO;
		readop = 0;
		break;
	default:
		/* TODO: what about BIO_DELETE??? */
		panic("Unsupported bio command %x\n", bio->bio_cmd);
	}

	/* Cheat with the sector length to avoid a non-constant division */
	blkcount = howmany(bio->bio_bcount, MFI_SECTOR_LEN);
	/* Fill the LBA and Transfer length in CDB */
	cdb_len = mfi_build_cdb(readop, 0, bio->bio_pblkno, blkcount,
	    pass->cdb);
	pass->header.target_id = (uintptr_t)bio->bio_driver1;
	pass->header.lun_id = 0;
	pass->header.timeout = 0;
	pass->header.flags = 0;
	pass->header.scsi_status = 0;
	pass->header.sense_len = MFI_SENSE_LEN;
	pass->header.data_len = bio->bio_bcount;
	pass->header.cdb_len = cdb_len;
	pass->sense_addr_lo = (uint32_t)cm->cm_sense_busaddr;
	pass->sense_addr_hi = (uint32_t)((uint64_t)cm->cm_sense_busaddr >> 32);
	cm->cm_complete = mfi_bio_complete;
	cm->cm_private = bio;
	cm->cm_data = unmapped_buf;
	cm->cm_len = bio->bio_bcount;
	cm->cm_sg = &pass->sgl;
	cm->cm_total_frame_size = MFI_PASS_FRAME_SIZE;
	cm->cm_flags = flags;

	return (cm);
}