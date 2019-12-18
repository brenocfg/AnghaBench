#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct mpt_softc {int dummy; } ;
struct TYPE_8__ {int IOCStatus; TYPE_3__* req_vbuf; } ;
typedef  TYPE_1__ request_t ;
struct TYPE_9__ {int PageNumber; int PageType; int /*<<< orphan*/  PageAddress; scalar_t__ PageLength; scalar_t__ PageVersion; int /*<<< orphan*/  Action; } ;
typedef  TYPE_2__ cfgparms_t ;
struct TYPE_10__ {int /*<<< orphan*/  Header; } ;
typedef  TYPE_3__ MSG_CONFIG ;
typedef  int /*<<< orphan*/  CONFIG_PAGE_HEADER ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MPI_CONFIG_ACTION_PAGE_HEADER ; 
#define  MPI_IOCSTATUS_CONFIG_INVALID_PAGE 129 
 int MPI_IOCSTATUS_MASK ; 
#define  MPI_IOCSTATUS_SUCCESS 128 
 int /*<<< orphan*/  MPT_PRT_DEBUG ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mpt_free_request (struct mpt_softc*,TYPE_1__*) ; 
 TYPE_1__* mpt_get_request (struct mpt_softc*,int) ; 
 int mpt_issue_cfg_req (struct mpt_softc*,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mpt_lprt (struct mpt_softc*,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*,...) ; 

int
mpt_read_cfg_header(struct mpt_softc *mpt, int PageType, int PageNumber,
		    uint32_t PageAddress, CONFIG_PAGE_HEADER *rslt,
		    int sleep_ok, int timeout_ms)
{
	request_t  *req;
	cfgparms_t params;
	MSG_CONFIG *cfgp;
	int	    error;

	req = mpt_get_request(mpt, sleep_ok);
	if (req == NULL) {
		mpt_prt(mpt, "mpt_read_cfg_header: Get request failed!\n");
		return (ENOMEM);
	}

	params.Action = MPI_CONFIG_ACTION_PAGE_HEADER;
	params.PageVersion = 0;
	params.PageLength = 0;
	params.PageNumber = PageNumber;
	params.PageType = PageType;
	params.PageAddress = PageAddress;
	error = mpt_issue_cfg_req(mpt, req, &params, /*addr*/0, /*len*/0,
				  sleep_ok, timeout_ms);
	if (error != 0) {
		/*
		 * Leave the request. Without resetting the chip, it's
		 * still owned by it and we'll just get into trouble
		 * freeing it now. Mark it as abandoned so that if it
		 * shows up later it can be freed.
		 */
		mpt_prt(mpt, "read_cfg_header timed out\n");
		return (ETIMEDOUT);
	}

        switch (req->IOCStatus & MPI_IOCSTATUS_MASK) {
	case MPI_IOCSTATUS_SUCCESS:
		cfgp = req->req_vbuf;
		bcopy(&cfgp->Header, rslt, sizeof(*rslt));
		error = 0;
		break;
	case MPI_IOCSTATUS_CONFIG_INVALID_PAGE:
		mpt_lprt(mpt, MPT_PRT_DEBUG,
		    "Invalid Page Type %d Number %d Addr 0x%0x\n",
		    PageType, PageNumber, PageAddress);
		error = EINVAL;
		break;
	default:
		mpt_prt(mpt, "mpt_read_cfg_header: Config Info Status %x\n",
			req->IOCStatus);
		error = EIO;
		break;
	}
	mpt_free_request(mpt, req);
	return (error);
}