#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mpt_softc {int dummy; } ;
typedef  int /*<<< orphan*/  request_t ;
struct TYPE_3__ {int Event; int EventDataLength; int /*<<< orphan*/ * Data; int /*<<< orphan*/  IOCLogInfo; } ;
typedef  TYPE_1__ MSG_EVENT_NOTIFY_REPLY ;

/* Variables and functions */
#define  MPI_EVENT_EVENT_CHANGE 131 
#define  MPI_EVENT_LOG_DATA 130 
#define  MPI_EVENT_NONE 129 
#define  MPI_EVENT_SAS_DEVICE_STATUS_CHANGE 128 
 int /*<<< orphan*/  MPT_PRT_DEBUG ; 
 int /*<<< orphan*/  mpt_lprt (struct mpt_softc*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*,...) ; 
 int /*<<< orphan*/  mpt_prtc (struct mpt_softc*,char*,...) ; 

__attribute__((used)) static int
mpt_core_event(struct mpt_softc *mpt, request_t *req,
	       MSG_EVENT_NOTIFY_REPLY *msg)
{

	mpt_lprt(mpt, MPT_PRT_DEBUG, "mpt_core_event: 0x%x\n",
                 msg->Event & 0xFF);
	switch(msg->Event & 0xFF) {
	case MPI_EVENT_NONE:
		break;
	case MPI_EVENT_LOG_DATA:
	{
		int i;

		/* Some error occurred that LSI wants logged */
		mpt_prt(mpt, "EvtLogData: IOCLogInfo: 0x%08x\n",
			msg->IOCLogInfo);
		mpt_prt(mpt, "\tEvtLogData: Event Data:");
		for (i = 0; i < msg->EventDataLength; i++)
			mpt_prtc(mpt, "  %08x", msg->Data[i]);
		mpt_prtc(mpt, "\n");
		break;
	}
	case MPI_EVENT_EVENT_CHANGE:
		/*
		 * This is just an acknowledgement
		 * of our mpt_send_event_request.
		 */
		break;
	case MPI_EVENT_SAS_DEVICE_STATUS_CHANGE:
		break;
	default:
		return (0);
		break;
	}
	return (1);
}