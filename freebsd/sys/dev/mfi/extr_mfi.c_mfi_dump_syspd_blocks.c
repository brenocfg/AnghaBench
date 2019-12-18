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
typedef  int uint64_t ;
typedef  void* uint32_t ;
struct mfi_softc {int /*<<< orphan*/  mfi_buffer_dmat; int /*<<< orphan*/  mfi_dev; } ;
struct TYPE_4__ {int target_id; int data_len; int cdb_len; int /*<<< orphan*/  sense_len; scalar_t__ scsi_status; scalar_t__ flags; scalar_t__ timeout; int /*<<< orphan*/  cmd; } ;
struct mfi_pass_frame {int /*<<< orphan*/  sgl; void* sense_addr_hi; void* sense_addr_lo; TYPE_2__ header; int /*<<< orphan*/  cdb; } ;
struct mfi_command {int cm_len; int cm_flags; int /*<<< orphan*/  cm_dmamap; int /*<<< orphan*/  cm_total_frame_size; int /*<<< orphan*/ * cm_sg; void* cm_data; scalar_t__ cm_sense_busaddr; TYPE_1__* cm_frame; } ;
struct TYPE_3__ {struct mfi_pass_frame pass; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int EBUSY ; 
 int MFI_CMD_DATAOUT ; 
 int /*<<< orphan*/  MFI_CMD_PD_SCSI_IO ; 
 int MFI_CMD_POLLED ; 
 int MFI_CMD_SCSI ; 
 int /*<<< orphan*/  MFI_PASS_FRAME_SIZE ; 
 int /*<<< orphan*/  MFI_SECTOR_LEN ; 
 int /*<<< orphan*/  MFI_SENSE_LEN ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 void* howmany (int,int /*<<< orphan*/ ) ; 
 int mfi_build_cdb (int,int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ ) ; 
 struct mfi_command* mfi_dequeue_free (struct mfi_softc*) ; 
 int mfi_mapcmd (struct mfi_softc*,struct mfi_command*) ; 
 int /*<<< orphan*/  mfi_release_command (struct mfi_command*) ; 

int
mfi_dump_syspd_blocks(struct mfi_softc *sc, int id, uint64_t lba, void *virt,
    int len)
{
	struct mfi_command *cm;
	struct mfi_pass_frame *pass;
	int error, readop, cdb_len;
	uint32_t blkcount;

	if ((cm = mfi_dequeue_free(sc)) == NULL)
		return (EBUSY);

	pass = &cm->cm_frame->pass;
	bzero(pass->cdb, 16);
	pass->header.cmd = MFI_CMD_PD_SCSI_IO;

	readop = 0;
	blkcount = howmany(len, MFI_SECTOR_LEN);
	cdb_len = mfi_build_cdb(readop, 0, lba, blkcount, pass->cdb);
	pass->header.target_id = id;
	pass->header.timeout = 0;
	pass->header.flags = 0;
	pass->header.scsi_status = 0;
	pass->header.sense_len = MFI_SENSE_LEN;
	pass->header.data_len = len;
	pass->header.cdb_len = cdb_len;
	pass->sense_addr_lo = (uint32_t)cm->cm_sense_busaddr;
	pass->sense_addr_hi = (uint32_t)((uint64_t)cm->cm_sense_busaddr >> 32);
	cm->cm_data = virt;
	cm->cm_len = len;
	cm->cm_sg = &pass->sgl;
	cm->cm_total_frame_size = MFI_PASS_FRAME_SIZE;
	cm->cm_flags = MFI_CMD_POLLED | MFI_CMD_DATAOUT | MFI_CMD_SCSI;

	if ((error = mfi_mapcmd(sc, cm)) != 0)
		device_printf(sc->mfi_dev, "failed dump blocks\n");
	bus_dmamap_sync(sc->mfi_buffer_dmat, cm->cm_dmamap,
	    BUS_DMASYNC_POSTWRITE);
	bus_dmamap_unload(sc->mfi_buffer_dmat, cm->cm_dmamap);
	mfi_release_command(cm);

	return (error);
}