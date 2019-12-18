#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct mpt_softc {int dummy; } ;
struct TYPE_12__ {int IOCStatus; TYPE_4__* req_vbuf; } ;
typedef  TYPE_2__ request_t ;
struct TYPE_13__ {int PageVersion; int PageNumber; int ExtPageType; scalar_t__ ExtPageLength; int /*<<< orphan*/  PageAddress; int /*<<< orphan*/  PageType; scalar_t__ PageLength; int /*<<< orphan*/  Action; } ;
typedef  TYPE_3__ cfgparms_t ;
struct TYPE_15__ {int /*<<< orphan*/  ExtPageType; int /*<<< orphan*/  ExtPageLength; int /*<<< orphan*/  PageType; int /*<<< orphan*/  PageNumber; int /*<<< orphan*/  PageVersion; } ;
struct TYPE_11__ {int /*<<< orphan*/  PageType; int /*<<< orphan*/  PageNumber; int /*<<< orphan*/  PageVersion; } ;
struct TYPE_14__ {int /*<<< orphan*/  ExtPageType; int /*<<< orphan*/  ExtPageLength; TYPE_1__ Header; } ;
typedef  TYPE_4__ MSG_CONFIG_REPLY ;
typedef  TYPE_5__ CONFIG_EXTENDED_PAGE_HEADER ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MPI_CONFIG_ACTION_PAGE_HEADER ; 
 int /*<<< orphan*/  MPI_CONFIG_PAGETYPE_EXTENDED ; 
#define  MPI_IOCSTATUS_CONFIG_INVALID_PAGE 129 
 int MPI_IOCSTATUS_MASK ; 
#define  MPI_IOCSTATUS_SUCCESS 128 
 int /*<<< orphan*/  MPT_PRT_DEBUG ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_free_request (struct mpt_softc*,TYPE_2__*) ; 
 TYPE_2__* mpt_get_request (struct mpt_softc*,int) ; 
 int mpt_issue_cfg_req (struct mpt_softc*,TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mpt_lprt (struct mpt_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*,...) ; 

int
mpt_read_extcfg_header(struct mpt_softc *mpt, int PageVersion, int PageNumber,
		       uint32_t PageAddress, int ExtPageType,
		       CONFIG_EXTENDED_PAGE_HEADER *rslt,
		       int sleep_ok, int timeout_ms)
{
	request_t  *req;
	cfgparms_t params;
	MSG_CONFIG_REPLY *cfgp;
	int	    error;

	req = mpt_get_request(mpt, sleep_ok);
	if (req == NULL) {
		mpt_prt(mpt, "mpt_extread_cfg_header: Get request failed!\n");
		return (ENOMEM);
	}

	params.Action = MPI_CONFIG_ACTION_PAGE_HEADER;
	params.PageVersion = PageVersion;
	params.PageLength = 0;
	params.PageNumber = PageNumber;
	params.PageType = MPI_CONFIG_PAGETYPE_EXTENDED;
	params.PageAddress = PageAddress;
	params.ExtPageType = ExtPageType;
	params.ExtPageLength = 0;
	error = mpt_issue_cfg_req(mpt, req, &params, /*addr*/0, /*len*/0,
				  sleep_ok, timeout_ms);
	if (error != 0) {
		/*
		 * Leave the request. Without resetting the chip, it's
		 * still owned by it and we'll just get into trouble
		 * freeing it now. Mark it as abandoned so that if it
		 * shows up later it can be freed.
		 */
		mpt_prt(mpt, "read_extcfg_header timed out\n");
		return (ETIMEDOUT);
	}

        switch (req->IOCStatus & MPI_IOCSTATUS_MASK) {
	case MPI_IOCSTATUS_SUCCESS:
		cfgp = req->req_vbuf;
		rslt->PageVersion = cfgp->Header.PageVersion;
		rslt->PageNumber = cfgp->Header.PageNumber;
		rslt->PageType = cfgp->Header.PageType;
		rslt->ExtPageLength = le16toh(cfgp->ExtPageLength);
		rslt->ExtPageType = cfgp->ExtPageType;
		error = 0;
		break;
	case MPI_IOCSTATUS_CONFIG_INVALID_PAGE:
		mpt_lprt(mpt, MPT_PRT_DEBUG,
		    "Invalid Page Type %d Number %d Addr 0x%0x\n",
		    MPI_CONFIG_PAGETYPE_EXTENDED, PageNumber, PageAddress);
		error = EINVAL;
		break;
	default:
		mpt_prt(mpt, "mpt_read_extcfg_header: Config Info Status %x\n",
			req->IOCStatus);
		error = EIO;
		break;
	}
	mpt_free_request(mpt, req);
	return (error);
}