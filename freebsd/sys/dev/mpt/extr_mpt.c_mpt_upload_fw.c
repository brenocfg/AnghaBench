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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct mpt_softc {int fw_image_size; int fw_phys; int /*<<< orphan*/  fw_dmap; int /*<<< orphan*/  fw_dmat; } ;
typedef  int /*<<< orphan*/  fw_req_buf ;
typedef  int /*<<< orphan*/  fw_reply ;
struct TYPE_6__ {int DetailsLength; void* ImageSize; int /*<<< orphan*/  Flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  SGL; void* MsgContext; int /*<<< orphan*/  Function; int /*<<< orphan*/  ImageType; } ;
struct TYPE_4__ {void* Address; void* FlagsLength; } ;
typedef  TYPE_1__ SGE_SIMPLE32 ;
typedef  int /*<<< orphan*/  MSG_FW_UPLOAD_REPLY ;
typedef  TYPE_2__ MSG_FW_UPLOAD ;
typedef  TYPE_3__ FW_UPLOAD_TCSGE ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int FW_UPLOAD_REQ_SIZE ; 
 int /*<<< orphan*/  MPI_FUNCTION_FW_UPLOAD ; 
 int /*<<< orphan*/  MPI_FW_UPLOAD_ITYPE_FW_IOC_MEM ; 
 int MPI_SGE_FLAGS_32_BIT_ADDRESSING ; 
 int MPI_SGE_FLAGS_END_OF_BUFFER ; 
 int MPI_SGE_FLAGS_END_OF_LIST ; 
 int MPI_SGE_FLAGS_IOC_TO_HOST ; 
 int MPI_SGE_FLAGS_LAST_ELEMENT ; 
 int MPI_SGE_FLAGS_SHIFT ; 
 int MPI_SGE_FLAGS_SIMPLE_ELEMENT ; 
 int /*<<< orphan*/  MPI_SGE_FLAGS_TRANSACTION_ELEMENT ; 
 int MPT_REPLY_HANDLER_HANDSHAKE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* htole32 (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int mpt_recv_handshake_reply (struct mpt_softc*,int,int /*<<< orphan*/ *) ; 
 int mpt_send_handshake_cmd (struct mpt_softc*,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
mpt_upload_fw(struct mpt_softc *mpt)
{
	uint8_t fw_req_buf[FW_UPLOAD_REQ_SIZE];
	MSG_FW_UPLOAD_REPLY fw_reply;
	MSG_FW_UPLOAD *fw_req;
	FW_UPLOAD_TCSGE *tsge;
	SGE_SIMPLE32 *sge;
	uint32_t flags;
	int error;
	
	memset(&fw_req_buf, 0, sizeof(fw_req_buf));
	fw_req = (MSG_FW_UPLOAD *)fw_req_buf;
	fw_req->ImageType = MPI_FW_UPLOAD_ITYPE_FW_IOC_MEM;
	fw_req->Function = MPI_FUNCTION_FW_UPLOAD;
	fw_req->MsgContext = htole32(MPT_REPLY_HANDLER_HANDSHAKE);
	tsge = (FW_UPLOAD_TCSGE *)&fw_req->SGL;
	tsge->DetailsLength = 12;
	tsge->Flags = MPI_SGE_FLAGS_TRANSACTION_ELEMENT;
	tsge->ImageSize = htole32(mpt->fw_image_size);
	sge = (SGE_SIMPLE32 *)(tsge + 1);
	flags = (MPI_SGE_FLAGS_LAST_ELEMENT | MPI_SGE_FLAGS_END_OF_BUFFER
	      | MPI_SGE_FLAGS_END_OF_LIST | MPI_SGE_FLAGS_SIMPLE_ELEMENT
	      | MPI_SGE_FLAGS_32_BIT_ADDRESSING | MPI_SGE_FLAGS_IOC_TO_HOST);
	flags <<= MPI_SGE_FLAGS_SHIFT;
	sge->FlagsLength = htole32(flags | mpt->fw_image_size);
	sge->Address = htole32(mpt->fw_phys);
	bus_dmamap_sync(mpt->fw_dmat, mpt->fw_dmap, BUS_DMASYNC_PREREAD);
	error = mpt_send_handshake_cmd(mpt, sizeof(fw_req_buf), &fw_req_buf);
	if (error)
		return(error);
	error = mpt_recv_handshake_reply(mpt, sizeof(fw_reply), &fw_reply);
	bus_dmamap_sync(mpt->fw_dmat, mpt->fw_dmap, BUS_DMASYNC_POSTREAD);
	return (error);
}