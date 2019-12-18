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
typedef  int u_int32_t ;
struct mrsas_softc {int max_fw_cmds; int reply_q_depth; int request_alloc_sz; int reply_alloc_sz; int io_frames_alloc_sz; int max_chain_frame_sz; int chain_frames_alloc_sz; int max_sge_in_main_msg; int max_sge_in_chain; int max_num_sge; int chain_offset_mfi_pthru; int chain_offset_io_request; int msix_vectors; scalar_t__* last_reply_idx; scalar_t__ max_scsi_cmds; } ;
typedef  int /*<<< orphan*/  MRSAS_REQUEST_DESCRIPTOR_UNION ;
typedef  int /*<<< orphan*/  MPI2_SGE_IO_UNION ;
typedef  int /*<<< orphan*/  MPI2_REPLY_DESCRIPTORS_UNION ;

/* Variables and functions */
 int MEGASAS_1MB_IO ; 
 int MEGASAS_256K_IO ; 
 int MEGASAS_MAX_CHAIN_SIZE_MASK ; 
 int MEGASAS_MAX_CHAIN_SIZE_UNITS_MASK ; 
 int MRSAS_FWSTATE_MAXCMD_MASK ; 
 int /*<<< orphan*/  MRSAS_INFO ; 
 scalar_t__ MRSAS_MAX_MFI_CMDS ; 
 int MRSAS_MPI2_RAID_DEFAULT_IO_FRAME_SIZE ; 
 int /*<<< orphan*/  MRSAS_RAID_SCSI_IO_REQUEST ; 
 int /*<<< orphan*/  SGL ; 
 int SUCCESS ; 
 int mrsas_alloc_mem (struct mrsas_softc*) ; 
 int mrsas_alloc_mpt_cmds (struct mrsas_softc*) ; 
 int /*<<< orphan*/  mrsas_dprint (struct mrsas_softc*,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int mrsas_ioc_init (struct mrsas_softc*) ; 
 void* mrsas_read_reg_with_retries (struct mrsas_softc*,int) ; 
 int /*<<< orphan*/  mrsas_reg_set ; 
 int offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outbound_scratch_pad ; 
 int /*<<< orphan*/  outbound_scratch_pad_2 ; 

int
mrsas_init_adapter(struct mrsas_softc *sc)
{
	uint32_t status;
	u_int32_t scratch_pad_2;
	int ret;
	int i = 0;

	/* Read FW status register */
	status = mrsas_read_reg_with_retries(sc, offsetof(mrsas_reg_set, outbound_scratch_pad));

	sc->max_fw_cmds = status & MRSAS_FWSTATE_MAXCMD_MASK;

	/* Decrement the max supported by 1, to correlate with FW */
	sc->max_fw_cmds = sc->max_fw_cmds - 1;
	sc->max_scsi_cmds = sc->max_fw_cmds - MRSAS_MAX_MFI_CMDS;

	/* Determine allocation size of command frames */
	sc->reply_q_depth = ((sc->max_fw_cmds + 1 + 15) / 16 * 16) * 2;
	sc->request_alloc_sz = sizeof(MRSAS_REQUEST_DESCRIPTOR_UNION) * sc->max_fw_cmds;
	sc->reply_alloc_sz = sizeof(MPI2_REPLY_DESCRIPTORS_UNION) * (sc->reply_q_depth);
	sc->io_frames_alloc_sz = MRSAS_MPI2_RAID_DEFAULT_IO_FRAME_SIZE +
	    (MRSAS_MPI2_RAID_DEFAULT_IO_FRAME_SIZE * (sc->max_fw_cmds + 1));
	scratch_pad_2 = mrsas_read_reg_with_retries(sc, offsetof(mrsas_reg_set,
	    outbound_scratch_pad_2));
	/*
	 * If scratch_pad_2 & MEGASAS_MAX_CHAIN_SIZE_UNITS_MASK is set,
	 * Firmware support extended IO chain frame which is 4 time more
	 * than legacy Firmware. Legacy Firmware - Frame size is (8 * 128) =
	 * 1K 1M IO Firmware  - Frame size is (8 * 128 * 4)  = 4K
	 */
	if (scratch_pad_2 & MEGASAS_MAX_CHAIN_SIZE_UNITS_MASK)
		sc->max_chain_frame_sz =
		    ((scratch_pad_2 & MEGASAS_MAX_CHAIN_SIZE_MASK) >> 5)
		    * MEGASAS_1MB_IO;
	else
		sc->max_chain_frame_sz =
		    ((scratch_pad_2 & MEGASAS_MAX_CHAIN_SIZE_MASK) >> 5)
		    * MEGASAS_256K_IO;

	sc->chain_frames_alloc_sz = sc->max_chain_frame_sz * sc->max_fw_cmds;
	sc->max_sge_in_main_msg = (MRSAS_MPI2_RAID_DEFAULT_IO_FRAME_SIZE -
	    offsetof(MRSAS_RAID_SCSI_IO_REQUEST, SGL)) / 16;

	sc->max_sge_in_chain = sc->max_chain_frame_sz / sizeof(MPI2_SGE_IO_UNION);
	sc->max_num_sge = sc->max_sge_in_main_msg + sc->max_sge_in_chain - 2;

	mrsas_dprint(sc, MRSAS_INFO,
	    "max sge: 0x%x, max chain frame size: 0x%x, "
	    "max fw cmd: 0x%x\n", sc->max_num_sge,
	    sc->max_chain_frame_sz, sc->max_fw_cmds);

	/* Used for pass thru MFI frame (DCMD) */
	sc->chain_offset_mfi_pthru = offsetof(MRSAS_RAID_SCSI_IO_REQUEST, SGL) / 16;

	sc->chain_offset_io_request = (MRSAS_MPI2_RAID_DEFAULT_IO_FRAME_SIZE -
	    sizeof(MPI2_SGE_IO_UNION)) / 16;

	int count = sc->msix_vectors > 0 ? sc->msix_vectors : 1;

	for (i = 0; i < count; i++)
		sc->last_reply_idx[i] = 0;

	ret = mrsas_alloc_mem(sc);
	if (ret != SUCCESS)
		return (ret);

	ret = mrsas_alloc_mpt_cmds(sc);
	if (ret != SUCCESS)
		return (ret);

	ret = mrsas_ioc_init(sc);
	if (ret != SUCCESS)
		return (ret);

	return (0);
}