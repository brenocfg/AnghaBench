#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct mpt_softc {int dummy; } ;
struct TYPE_9__ {int req_pbuf; int IOCStatus; scalar_t__ req_vbuf; } ;
typedef  TYPE_1__ request_t ;
struct TYPE_10__ {int Action; int /*<<< orphan*/  ExtPageLength; int /*<<< orphan*/  ExtPageType; int /*<<< orphan*/  PageAddress; int /*<<< orphan*/  PageType; int /*<<< orphan*/  PageNumber; scalar_t__ PageLength; int /*<<< orphan*/  PageVersion; } ;
typedef  TYPE_2__ cfgparms_t ;
struct TYPE_11__ {int /*<<< orphan*/  ExtPageLength; int /*<<< orphan*/  ExtPageType; int /*<<< orphan*/  PageNumber; int /*<<< orphan*/  PageVersion; } ;
typedef  TYPE_3__ CONFIG_EXTENDED_PAGE_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  MPI_CONFIG_PAGETYPE_EXTENDED ; 
 int MPI_IOCSTATUS_MASK ; 
 int MPI_IOCSTATUS_SUCCESS ; 
 int MPT_RQSL (struct mpt_softc*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  mpt_free_request (struct mpt_softc*,TYPE_1__*) ; 
 TYPE_1__* mpt_get_request (struct mpt_softc*,int) ; 
 int mpt_issue_cfg_req (struct mpt_softc*,TYPE_1__*,TYPE_2__*,int,size_t,int,int) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*,...) ; 

int
mpt_read_extcfg_page(struct mpt_softc *mpt, int Action, uint32_t PageAddress,
		     CONFIG_EXTENDED_PAGE_HEADER *hdr, void *buf, size_t len,
		     int sleep_ok, int timeout_ms)
{
	request_t    *req;
	cfgparms_t    params;
	int	      error;

	req = mpt_get_request(mpt, sleep_ok);
	if (req == NULL) {
		mpt_prt(mpt, "mpt_read_extcfg_page: Get request failed!\n");
		return (-1);
	}

	params.Action = Action;
	params.PageVersion = hdr->PageVersion;
	params.PageLength = 0;
	params.PageNumber = hdr->PageNumber;
	params.PageType = MPI_CONFIG_PAGETYPE_EXTENDED;
	params.PageAddress = PageAddress;
	params.ExtPageType = hdr->ExtPageType;
	params.ExtPageLength = hdr->ExtPageLength;
	error = mpt_issue_cfg_req(mpt, req, &params,
				  req->req_pbuf + MPT_RQSL(mpt),
				  len, sleep_ok, timeout_ms);
	if (error != 0) {
		mpt_prt(mpt, "read_extcfg_page(%d) timed out\n", Action);
		return (-1);
	}

	if ((req->IOCStatus & MPI_IOCSTATUS_MASK) != MPI_IOCSTATUS_SUCCESS) {
		mpt_prt(mpt, "mpt_read_extcfg_page: Config Info Status %x\n",
			req->IOCStatus);
		mpt_free_request(mpt, req);
		return (-1);
	}
	memcpy(buf, ((uint8_t *)req->req_vbuf)+MPT_RQSL(mpt), len);
	mpt_free_request(mpt, req);
	return (0);
}