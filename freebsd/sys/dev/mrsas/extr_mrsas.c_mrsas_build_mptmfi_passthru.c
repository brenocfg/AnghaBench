#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int8_t ;
struct mrsas_softc {int max_sge_in_main_msg; int /*<<< orphan*/  max_chain_frame_sz; int /*<<< orphan*/  chain_offset_mfi_pthru; scalar_t__ is_aero; scalar_t__ is_ventura; scalar_t__ mrsas_gen3_ctrl; } ;
struct mrsas_mpt_cmd {int flags; TYPE_6__* io_request; int /*<<< orphan*/  sync_cmd_idx; int /*<<< orphan*/  index; } ;
struct TYPE_9__ {int /*<<< orphan*/  smid; } ;
struct TYPE_10__ {TYPE_2__ context; } ;
struct mrsas_mfi_cmd {int /*<<< orphan*/  frame_phys_addr; int /*<<< orphan*/  index; TYPE_3__ cmd_id; TYPE_1__* frame; } ;
struct mrsas_header {int flags; } ;
typedef  TYPE_5__* pMpi25IeeeSgeChain64_t ;
struct TYPE_14__ {int Flags; int /*<<< orphan*/  Length; int /*<<< orphan*/  Address; } ;
struct TYPE_11__ {int /*<<< orphan*/  IeeeChain; } ;
struct TYPE_13__ {int SGLOffset0; int /*<<< orphan*/  ChainOffset; int /*<<< orphan*/  Function; TYPE_4__ SGL; } ;
struct TYPE_12__ {scalar_t__ Flags; } ;
struct TYPE_8__ {struct mrsas_header hdr; } ;
typedef  TYPE_6__* PTR_MRSAS_RAID_SCSI_IO_REQUEST ;
typedef  TYPE_7__ MPI25_IEEE_SGE_CHAIN64 ;

/* Variables and functions */
 int IEEE_SGE_FLAGS_CHAIN_ELEMENT ; 
 int MFI_FRAME_DONT_POST_IN_REPLY_QUEUE ; 
 int MPI2_IEEE_SGE_FLAGS_IOCPLBNTA_ADDR ; 
 int /*<<< orphan*/  MRSAS_MPI2_FUNCTION_PASSTHRU_IO_REQUEST ; 
 int /*<<< orphan*/  MRSAS_RAID_SCSI_IO_REQUEST ; 
 int /*<<< orphan*/  SGL ; 
 struct mrsas_mpt_cmd* mrsas_get_mpt_cmd (struct mrsas_softc*) ; 
 int offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u_int8_t
mrsas_build_mptmfi_passthru(struct mrsas_softc *sc, struct mrsas_mfi_cmd *mfi_cmd)
{
	MPI25_IEEE_SGE_CHAIN64 *mpi25_ieee_chain;
	PTR_MRSAS_RAID_SCSI_IO_REQUEST io_req;
	struct mrsas_mpt_cmd *mpt_cmd;
	struct mrsas_header *frame_hdr = &mfi_cmd->frame->hdr;

	mpt_cmd = mrsas_get_mpt_cmd(sc);
	if (!mpt_cmd)
		return (1);

	/* Save the smid. To be used for returning the cmd */
	mfi_cmd->cmd_id.context.smid = mpt_cmd->index;

	mpt_cmd->sync_cmd_idx = mfi_cmd->index;

	/*
	 * For cmds where the flag is set, store the flag and check on
	 * completion. For cmds with this flag, don't call
	 * mrsas_complete_cmd.
	 */

	if (frame_hdr->flags & MFI_FRAME_DONT_POST_IN_REPLY_QUEUE)
		mpt_cmd->flags = MFI_FRAME_DONT_POST_IN_REPLY_QUEUE;

	io_req = mpt_cmd->io_request;

	if (sc->mrsas_gen3_ctrl || sc->is_ventura || sc->is_aero) {
		pMpi25IeeeSgeChain64_t sgl_ptr_end = (pMpi25IeeeSgeChain64_t)&io_req->SGL;

		sgl_ptr_end += sc->max_sge_in_main_msg - 1;
		sgl_ptr_end->Flags = 0;
	}
	mpi25_ieee_chain = (MPI25_IEEE_SGE_CHAIN64 *) & io_req->SGL.IeeeChain;

	io_req->Function = MRSAS_MPI2_FUNCTION_PASSTHRU_IO_REQUEST;
	io_req->SGLOffset0 = offsetof(MRSAS_RAID_SCSI_IO_REQUEST, SGL) / 4;
	io_req->ChainOffset = sc->chain_offset_mfi_pthru;

	mpi25_ieee_chain->Address = mfi_cmd->frame_phys_addr;

	mpi25_ieee_chain->Flags = IEEE_SGE_FLAGS_CHAIN_ELEMENT |
	    MPI2_IEEE_SGE_FLAGS_IOCPLBNTA_ADDR;

	mpi25_ieee_chain->Length = sc->max_chain_frame_sz;

	return (0);
}