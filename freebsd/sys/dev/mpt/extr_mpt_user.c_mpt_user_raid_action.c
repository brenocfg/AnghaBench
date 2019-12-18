#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct mpt_user_raid_action_result {int /*<<< orphan*/  action_data; int /*<<< orphan*/  action_status; int /*<<< orphan*/  volume_status; } ;
struct mpt_softc {int dummy; } ;
struct mpt_raid_action {scalar_t__ len; int /*<<< orphan*/  action_data; int /*<<< orphan*/  action_status; int /*<<< orphan*/  volume_status; int /*<<< orphan*/  ioc_status; scalar_t__ write; int /*<<< orphan*/  phys_disk_num; int /*<<< orphan*/  volume_bus; int /*<<< orphan*/  volume_id; int /*<<< orphan*/  action_data_word; int /*<<< orphan*/  action; } ;
struct mpt_page_memory {int paddr; int /*<<< orphan*/  map; int /*<<< orphan*/  tag; int /*<<< orphan*/ * vaddr; } ;
struct TYPE_11__ {int index; int IOCStatus; TYPE_3__* req_vbuf; } ;
typedef  TYPE_1__ request_t ;
struct TYPE_13__ {void* MsgContext; int /*<<< orphan*/  ActionDataSGE; int /*<<< orphan*/  PhysDiskNum; int /*<<< orphan*/  VolumeBus; int /*<<< orphan*/  VolumeID; int /*<<< orphan*/  Function; int /*<<< orphan*/  ActionDataWord; int /*<<< orphan*/  Action; } ;
struct TYPE_12__ {int FlagsLength; void* Address; } ;
typedef  TYPE_2__ SGE_SIMPLE32 ;
typedef  TYPE_3__ MSG_RAID_ACTION_REQUEST ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MPI_FUNCTION_RAID_ACTION ; 
 int MPI_IOCSTATUS_MASK ; 
 int MPI_IOCSTATUS_SUCCESS ; 
 int MPI_SGE_FLAGS_END_OF_BUFFER ; 
 int MPI_SGE_FLAGS_END_OF_LIST ; 
 int MPI_SGE_FLAGS_HOST_TO_IOC ; 
 int MPI_SGE_FLAGS_IOC_TO_HOST ; 
 int MPI_SGE_FLAGS_LAST_ELEMENT ; 
 int MPI_SGE_FLAGS_SIMPLE_ELEMENT ; 
 int /*<<< orphan*/  MPI_pSGE_SET_FLAGS (TYPE_2__*,int) ; 
 int /*<<< orphan*/  MPI_pSGE_SET_LENGTH (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int MPT_RQSL (struct mpt_softc*) ; 
 int /*<<< orphan*/  REQ_STATE_DONE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  htole16 (int) ; 
 void* htole32 (int) ; 
 int /*<<< orphan*/  le32toh (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpt_check_doorbell (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_free_request (struct mpt_softc*,TYPE_1__*) ; 
 TYPE_1__* mpt_get_request (struct mpt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*) ; 
 int /*<<< orphan*/  mpt_send_cmd (struct mpt_softc*,TYPE_1__*) ; 
 int mpt_wait_req (struct mpt_softc*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int user_handler_id ; 

__attribute__((used)) static int
mpt_user_raid_action(struct mpt_softc *mpt, struct mpt_raid_action *raid_act,
	struct mpt_page_memory *mpt_page)
{
	request_t *req;
	struct mpt_user_raid_action_result *res;
	MSG_RAID_ACTION_REQUEST *rap;
	SGE_SIMPLE32 *se;
	int error;

	req = mpt_get_request(mpt, TRUE);
	if (req == NULL)
		return (ENOMEM);
	rap = req->req_vbuf;
	memset(rap, 0, sizeof *rap);
	rap->Action = raid_act->action;
	rap->ActionDataWord = raid_act->action_data_word;
	rap->Function = MPI_FUNCTION_RAID_ACTION;
	rap->VolumeID = raid_act->volume_id;
	rap->VolumeBus = raid_act->volume_bus;
	rap->PhysDiskNum = raid_act->phys_disk_num;
	se = (SGE_SIMPLE32 *)&rap->ActionDataSGE;
	if (mpt_page->vaddr != NULL && raid_act->len != 0) {
		bus_dmamap_sync(mpt_page->tag, mpt_page->map,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
		se->Address = htole32(mpt_page->paddr);
		MPI_pSGE_SET_LENGTH(se, le32toh(raid_act->len));
		MPI_pSGE_SET_FLAGS(se, (MPI_SGE_FLAGS_SIMPLE_ELEMENT |
		    MPI_SGE_FLAGS_LAST_ELEMENT | MPI_SGE_FLAGS_END_OF_BUFFER |
		    MPI_SGE_FLAGS_END_OF_LIST |
		    (raid_act->write ? MPI_SGE_FLAGS_HOST_TO_IOC :
		    MPI_SGE_FLAGS_IOC_TO_HOST)));
	}
	se->FlagsLength = htole32(se->FlagsLength);
	rap->MsgContext = htole32(req->index | user_handler_id);

	mpt_check_doorbell(mpt);
	mpt_send_cmd(mpt, req);

	error = mpt_wait_req(mpt, req, REQ_STATE_DONE, REQ_STATE_DONE, TRUE,
	    2000);
	if (error != 0) {
		/*
		 * Leave request so it can be cleaned up later.
		 */
		mpt_prt(mpt, "mpt_user_raid_action timed out\n");
		return (error);
	}

	raid_act->ioc_status = htole16(req->IOCStatus);
	if ((req->IOCStatus & MPI_IOCSTATUS_MASK) != MPI_IOCSTATUS_SUCCESS) {
		mpt_free_request(mpt, req);
		return (0);
	}
	
	res = (struct mpt_user_raid_action_result *)
	    (((uint8_t *)req->req_vbuf) + MPT_RQSL(mpt));
	raid_act->volume_status = res->volume_status;
	raid_act->action_status = res->action_status;
	bcopy(res->action_data, raid_act->action_data,
	    sizeof(res->action_data));
	if (mpt_page->vaddr != NULL)
		bus_dmamap_sync(mpt_page->tag, mpt_page->map,
		    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
	mpt_free_request(mpt, req);
	return (0);
}