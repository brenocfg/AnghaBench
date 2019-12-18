#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int data_len; int cmd_status; int /*<<< orphan*/  cmd; int /*<<< orphan*/  flags; } ;
struct mfi_init_frame {TYPE_3__ header; void* qinfo_new_addr_hi; void* qinfo_new_addr_lo; void* driver_ver_hi; void* driver_ver_lo; } ;
struct TYPE_5__ {scalar_t__ context; } ;
union mfi_frame {struct mfi_init_frame init; TYPE_1__ header; } ;
typedef  int uint64_t ;
typedef  void* uint32_t ;
typedef  scalar_t__ uint16_t ;
struct mfi_softc {int MFA_enabled; int raid_io_msg_size; uintptr_t request_message_pool; uintptr_t request_message_pool_align; int /*<<< orphan*/  mfi_dev; scalar_t__ mfi_tb_ioc_init_busaddr; scalar_t__ verbuf_h_busaddr; scalar_t__ verbuf; scalar_t__ mfi_tb_busaddr; scalar_t__ reply_frame_pool_align; scalar_t__ mfi_max_fw_cmds; scalar_t__ mfi_tb_ioc_init_desc; int /*<<< orphan*/  mfi_tb_init_dmamap; scalar_t__ mfi_tb_init_busaddr; scalar_t__ mfi_tb_init; int /*<<< orphan*/  mfi_io_lock; } ;
struct mfi_command {int /*<<< orphan*/  cm_dmamap; scalar_t__ cm_frame_busaddr; union mfi_frame* cm_frame; void* cm_timestamp; int /*<<< orphan*/  cm_flags; int /*<<< orphan*/ * cm_data; } ;
struct MPI2_IOC_INIT_REQUEST {int SystemRequestFrameSize; void* TimeStamp; scalar_t__ ReplyFreeQueueAddress; int /*<<< orphan*/  SystemRequestFrameBaseAddress; int /*<<< orphan*/  ReplyDescriptorPostQueueAddress; scalar_t__ ReplyFreeQueueDepth; scalar_t__ ReplyDescriptorPostQueueDepth; int /*<<< orphan*/  HeaderVersion; int /*<<< orphan*/  MsgVersion; int /*<<< orphan*/  WhoInit; int /*<<< orphan*/  Function; } ;
typedef  scalar_t__ bus_addr_t ;
struct TYPE_6__ {void* addressHigh; void* addressLow; } ;
struct TYPE_8__ {TYPE_2__ u; } ;
typedef  TYPE_4__ MFI_ADDRESS ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  MA_OWNED ; 
 char* MEGASAS_VERSION ; 
 int /*<<< orphan*/  MFI_CMD_INIT ; 
 int /*<<< orphan*/  MFI_CMD_POLLED ; 
 int /*<<< orphan*/  MFI_FRAME_DONT_POST_IN_REPLY_QUEUE ; 
 int MFI_STAT_INVALID_STATUS ; 
 int MFI_STAT_OK ; 
 int /*<<< orphan*/  MPI2_FUNCTION_IOC_INIT ; 
 int /*<<< orphan*/  MPI2_HEADER_VERSION ; 
 int /*<<< orphan*/  MPI2_VERSION ; 
 int /*<<< orphan*/  MPI2_WHOINIT_HOST_DRIVER ; 
 int /*<<< orphan*/  bzero (struct MPI2_IOC_INIT_REQUEST*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct mfi_command* mfi_dequeue_free (struct mfi_softc*) ; 
 int mfi_mapcmd (struct mfi_softc*,struct mfi_command*) ; 
 int /*<<< orphan*/  mfi_release_command (struct mfi_command*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,scalar_t__,char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 void* time_uptime ; 

int
mfi_tbolt_init_MFI_queue(struct mfi_softc *sc)
{
	struct MPI2_IOC_INIT_REQUEST   *mpi2IocInit;
	struct mfi_init_frame		*mfi_init;
	uintptr_t			offset = 0;
	bus_addr_t			phyAddress;
	MFI_ADDRESS			*mfiAddressTemp;
	struct mfi_command		*cm, cmd_tmp;
	int error;

	mtx_assert(&sc->mfi_io_lock, MA_OWNED);

	/* Check if initialization is already completed */
	if (sc->MFA_enabled) {
		device_printf(sc->mfi_dev, "tbolt_init already initialised!\n");
		return 1;
	}

	if ((cm = mfi_dequeue_free(sc)) == NULL) {
		device_printf(sc->mfi_dev, "tbolt_init failed to get command "
		    " entry!\n");
		return (EBUSY);
	}

	cmd_tmp.cm_frame = cm->cm_frame;
	cmd_tmp.cm_frame_busaddr = cm->cm_frame_busaddr;
	cmd_tmp.cm_dmamap = cm->cm_dmamap;

	cm->cm_frame = (union mfi_frame *)((uintptr_t)sc->mfi_tb_init);
	cm->cm_frame_busaddr = sc->mfi_tb_init_busaddr;
	cm->cm_dmamap = sc->mfi_tb_init_dmamap;
	cm->cm_frame->header.context = 0;

	/*
	 * Abuse the SG list area of the frame to hold the init_qinfo
	 * object;
	 */
	mfi_init = &cm->cm_frame->init;

	mpi2IocInit = (struct MPI2_IOC_INIT_REQUEST *)sc->mfi_tb_ioc_init_desc;
	bzero(mpi2IocInit, sizeof(struct MPI2_IOC_INIT_REQUEST));
	mpi2IocInit->Function  = MPI2_FUNCTION_IOC_INIT;
	mpi2IocInit->WhoInit   = MPI2_WHOINIT_HOST_DRIVER;

	/* set MsgVersion and HeaderVersion host driver was built with */
	mpi2IocInit->MsgVersion = MPI2_VERSION;
	mpi2IocInit->HeaderVersion = MPI2_HEADER_VERSION;
	mpi2IocInit->SystemRequestFrameSize = sc->raid_io_msg_size/4;
	mpi2IocInit->ReplyDescriptorPostQueueDepth
	    = (uint16_t)sc->mfi_max_fw_cmds;
	mpi2IocInit->ReplyFreeQueueDepth = 0; /* Not supported by MR. */

	/* Get physical address of reply frame pool */
	offset = (uintptr_t) sc->reply_frame_pool_align
	    - (uintptr_t)sc->request_message_pool;
	phyAddress = sc->mfi_tb_busaddr + offset;
	mfiAddressTemp =
	    (MFI_ADDRESS *)&mpi2IocInit->ReplyDescriptorPostQueueAddress;
	mfiAddressTemp->u.addressLow = (uint32_t)phyAddress;
	mfiAddressTemp->u.addressHigh = (uint32_t)((uint64_t)phyAddress >> 32);

	/* Get physical address of request message pool */
	offset = sc->request_message_pool_align - sc->request_message_pool;
	phyAddress =  sc->mfi_tb_busaddr + offset;
	mfiAddressTemp = (MFI_ADDRESS *)&mpi2IocInit->SystemRequestFrameBaseAddress;
	mfiAddressTemp->u.addressLow = (uint32_t)phyAddress;
	mfiAddressTemp->u.addressHigh = (uint32_t)((uint64_t)phyAddress >> 32);
	mpi2IocInit->ReplyFreeQueueAddress =  0; /* Not supported by MR. */
	mpi2IocInit->TimeStamp = time_uptime;

	if (sc->verbuf) {
		snprintf((char *)sc->verbuf, strlen(MEGASAS_VERSION) + 2, "%s\n",
                MEGASAS_VERSION);
		mfi_init->driver_ver_lo = (uint32_t)sc->verbuf_h_busaddr;
		mfi_init->driver_ver_hi =
		    (uint32_t)((uint64_t)sc->verbuf_h_busaddr >> 32);
	}
	/* Get the physical address of the mpi2 ioc init command */
	phyAddress =  sc->mfi_tb_ioc_init_busaddr;
	mfi_init->qinfo_new_addr_lo = (uint32_t)phyAddress;
	mfi_init->qinfo_new_addr_hi = (uint32_t)((uint64_t)phyAddress >> 32);
	mfi_init->header.flags |= MFI_FRAME_DONT_POST_IN_REPLY_QUEUE;

	mfi_init->header.cmd = MFI_CMD_INIT;
	mfi_init->header.data_len = sizeof(struct MPI2_IOC_INIT_REQUEST);
	mfi_init->header.cmd_status = MFI_STAT_INVALID_STATUS;

	cm->cm_data = NULL;
	cm->cm_flags |= MFI_CMD_POLLED;
	cm->cm_timestamp = time_uptime;
	if ((error = mfi_mapcmd(sc, cm)) != 0) {
		device_printf(sc->mfi_dev, "failed to send IOC init2 "
		    "command %d at %lx\n", error, (long)cm->cm_frame_busaddr);
		goto out;
	}

	if (mfi_init->header.cmd_status == MFI_STAT_OK) {
		sc->MFA_enabled = 1;
	} else {
		device_printf(sc->mfi_dev, "Init command Failed %#x\n",
		    mfi_init->header.cmd_status);
		error = mfi_init->header.cmd_status;
		goto out;
	}

out:
	cm->cm_frame = cmd_tmp.cm_frame;
	cm->cm_frame_busaddr = cmd_tmp.cm_frame_busaddr;
	cm->cm_dmamap = cmd_tmp.cm_dmamap;
	mfi_release_command(cm);

	return (error);

}