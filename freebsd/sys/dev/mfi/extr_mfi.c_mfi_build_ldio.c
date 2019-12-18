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
typedef  union mfi_frame {int dummy; } mfi_frame ;
typedef  int uint64_t ;
typedef  void* uint32_t ;
struct mfi_softc {int /*<<< orphan*/  mfi_io_lock; } ;
struct TYPE_5__ {uintptr_t target_id; void* data_len; int /*<<< orphan*/  sense_len; scalar_t__ scsi_status; int /*<<< orphan*/  flags; scalar_t__ timeout; int /*<<< orphan*/  cmd; } ;
struct mfi_io_frame {int lba_hi; int lba_lo; int /*<<< orphan*/  sgl; void* sense_addr_hi; void* sense_addr_lo; TYPE_2__ header; } ;
struct mfi_command {int cm_flags; int /*<<< orphan*/  cm_total_frame_size; int /*<<< orphan*/ * cm_sg; int /*<<< orphan*/  cm_len; int /*<<< orphan*/  cm_data; struct bio* cm_private; int /*<<< orphan*/  cm_complete; scalar_t__ cm_sense_busaddr; TYPE_3__* cm_frame; } ;
struct bio {int bio_cmd; int bio_pblkno; int /*<<< orphan*/  bio_bcount; scalar_t__ bio_driver1; } ;
struct TYPE_4__ {void* context; } ;
struct TYPE_6__ {struct mfi_io_frame io; TYPE_1__ header; } ;

/* Variables and functions */
#define  BIO_READ 129 
#define  BIO_WRITE 128 
 int /*<<< orphan*/  MA_OWNED ; 
 int MFI_CMD_BIO ; 
 int MFI_CMD_DATAIN ; 
 int MFI_CMD_DATAOUT ; 
 int /*<<< orphan*/  MFI_CMD_LD_READ ; 
 int /*<<< orphan*/  MFI_CMD_LD_WRITE ; 
 int /*<<< orphan*/  MFI_IO_FRAME_SIZE ; 
 int /*<<< orphan*/  MFI_SECTOR_LEN ; 
 int /*<<< orphan*/  MFI_SENSE_LEN ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 void* howmany (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfi_bio_complete ; 
 struct mfi_command* mfi_dequeue_free (struct mfi_softc*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  unmapped_buf ; 

__attribute__((used)) static struct mfi_command *
mfi_build_ldio(struct mfi_softc *sc, struct bio *bio)
{
	struct mfi_io_frame *io;
	struct mfi_command *cm;
	int flags;
	uint32_t blkcount;
	uint32_t context = 0;

	mtx_assert(&sc->mfi_io_lock, MA_OWNED);

	if ((cm = mfi_dequeue_free(sc)) == NULL)
	    return (NULL);

	/* Zero out the MFI frame */
	context = cm->cm_frame->header.context;
	bzero(cm->cm_frame, sizeof(union mfi_frame));
	cm->cm_frame->header.context = context;
	io = &cm->cm_frame->io;
	switch (bio->bio_cmd) {
	case BIO_READ:
		io->header.cmd = MFI_CMD_LD_READ;
		flags = MFI_CMD_DATAIN | MFI_CMD_BIO;
		break;
	case BIO_WRITE:
		io->header.cmd = MFI_CMD_LD_WRITE;
		flags = MFI_CMD_DATAOUT | MFI_CMD_BIO;
		break;
	default:
		/* TODO: what about BIO_DELETE??? */
		panic("Unsupported bio command %x\n", bio->bio_cmd);
	}

	/* Cheat with the sector length to avoid a non-constant division */
	blkcount = howmany(bio->bio_bcount, MFI_SECTOR_LEN);
	io->header.target_id = (uintptr_t)bio->bio_driver1;
	io->header.timeout = 0;
	io->header.flags = 0;
	io->header.scsi_status = 0;
	io->header.sense_len = MFI_SENSE_LEN;
	io->header.data_len = blkcount;
	io->sense_addr_lo = (uint32_t)cm->cm_sense_busaddr;
	io->sense_addr_hi = (uint32_t)((uint64_t)cm->cm_sense_busaddr >> 32);
	io->lba_hi = (bio->bio_pblkno & 0xffffffff00000000) >> 32;
	io->lba_lo = bio->bio_pblkno & 0xffffffff;
	cm->cm_complete = mfi_bio_complete;
	cm->cm_private = bio;
	cm->cm_data = unmapped_buf;
	cm->cm_len = bio->bio_bcount;
	cm->cm_sg = &io->sgl;
	cm->cm_total_frame_size = MFI_IO_FRAME_SIZE;
	cm->cm_flags = flags;

	return (cm);
}