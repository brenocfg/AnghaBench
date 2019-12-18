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
struct mfi_softc {int /*<<< orphan*/  mfi_buffer_dmat; int /*<<< orphan*/  mfi_dev; } ;
struct TYPE_5__ {int target_id; int /*<<< orphan*/  data_len; int /*<<< orphan*/  sense_len; scalar_t__ scsi_status; scalar_t__ flags; scalar_t__ timeout; int /*<<< orphan*/  cmd; } ;
struct mfi_io_frame {int lba_hi; int lba_lo; int /*<<< orphan*/  sgl; void* sense_addr_hi; void* sense_addr_lo; TYPE_2__ header; } ;
struct mfi_command {int cm_len; int cm_flags; int /*<<< orphan*/  cm_dmamap; int /*<<< orphan*/  cm_total_frame_size; int /*<<< orphan*/ * cm_sg; void* cm_data; scalar_t__ cm_sense_busaddr; TYPE_3__* cm_frame; } ;
struct TYPE_4__ {void* context; } ;
struct TYPE_6__ {struct mfi_io_frame io; TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int EBUSY ; 
 int MFI_CMD_DATAOUT ; 
 int /*<<< orphan*/  MFI_CMD_LD_WRITE ; 
 int MFI_CMD_POLLED ; 
 int /*<<< orphan*/  MFI_IO_FRAME_SIZE ; 
 int /*<<< orphan*/  MFI_SECTOR_LEN ; 
 int /*<<< orphan*/  MFI_SENSE_LEN ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  howmany (int,int /*<<< orphan*/ ) ; 
 struct mfi_command* mfi_dequeue_free (struct mfi_softc*) ; 
 int mfi_mapcmd (struct mfi_softc*,struct mfi_command*) ; 
 int /*<<< orphan*/  mfi_release_command (struct mfi_command*) ; 

int
mfi_dump_blocks(struct mfi_softc *sc, int id, uint64_t lba, void *virt,
     int len)
{
	struct mfi_command *cm;
	struct mfi_io_frame *io;
	int error;
	uint32_t context = 0;

	if ((cm = mfi_dequeue_free(sc)) == NULL)
		return (EBUSY);

	/* Zero out the MFI frame */
	context = cm->cm_frame->header.context;
	bzero(cm->cm_frame, sizeof(union mfi_frame));
	cm->cm_frame->header.context = context;

	io = &cm->cm_frame->io;
	io->header.cmd = MFI_CMD_LD_WRITE;
	io->header.target_id = id;
	io->header.timeout = 0;
	io->header.flags = 0;
	io->header.scsi_status = 0;
	io->header.sense_len = MFI_SENSE_LEN;
	io->header.data_len = howmany(len, MFI_SECTOR_LEN);
	io->sense_addr_lo = (uint32_t)cm->cm_sense_busaddr;
	io->sense_addr_hi = (uint32_t)((uint64_t)cm->cm_sense_busaddr >> 32);
	io->lba_hi = (lba & 0xffffffff00000000) >> 32;
	io->lba_lo = lba & 0xffffffff;
	cm->cm_data = virt;
	cm->cm_len = len;
	cm->cm_sg = &io->sgl;
	cm->cm_total_frame_size = MFI_IO_FRAME_SIZE;
	cm->cm_flags = MFI_CMD_POLLED | MFI_CMD_DATAOUT;

	if ((error = mfi_mapcmd(sc, cm)) != 0)
		device_printf(sc->mfi_dev, "failed dump blocks\n");
	bus_dmamap_sync(sc->mfi_buffer_dmat, cm->cm_dmamap,
	    BUS_DMASYNC_POSTWRITE);
	bus_dmamap_unload(sc->mfi_buffer_dmat, cm->cm_dmamap);
	mfi_release_command(cm);

	return (error);
}