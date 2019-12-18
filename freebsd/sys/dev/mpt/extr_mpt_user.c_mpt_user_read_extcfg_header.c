#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct mpt_softc {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  ExtPageType; int /*<<< orphan*/  ExtPageLength; int /*<<< orphan*/  PageType; int /*<<< orphan*/  PageNumber; int /*<<< orphan*/  PageVersion; } ;
struct mpt_ext_cfg_page_req {TYPE_2__ header; int /*<<< orphan*/  ioc_status; int /*<<< orphan*/  page_address; } ;
struct TYPE_12__ {int IOCStatus; TYPE_5__* req_vbuf; } ;
typedef  TYPE_3__ request_t ;
struct TYPE_13__ {scalar_t__ ExtPageLength; int /*<<< orphan*/  ExtPageType; int /*<<< orphan*/  PageAddress; int /*<<< orphan*/  PageType; int /*<<< orphan*/  PageNumber; scalar_t__ PageLength; int /*<<< orphan*/  PageVersion; int /*<<< orphan*/  Action; } ;
typedef  TYPE_4__ cfgparms_t ;
struct TYPE_10__ {int /*<<< orphan*/  PageType; int /*<<< orphan*/  PageNumber; int /*<<< orphan*/  PageVersion; } ;
struct TYPE_14__ {int /*<<< orphan*/  ExtPageType; int /*<<< orphan*/  ExtPageLength; TYPE_1__ Header; } ;
typedef  TYPE_5__ MSG_CONFIG_REPLY ;

/* Variables and functions */
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MPI_CONFIG_ACTION_PAGE_HEADER ; 
 int /*<<< orphan*/  MPI_CONFIG_PAGETYPE_EXTENDED ; 
 int MPI_IOCSTATUS_MASK ; 
 int MPI_IOCSTATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  htole16 (int) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_free_request (struct mpt_softc*,TYPE_3__*) ; 
 TYPE_3__* mpt_get_request (struct mpt_softc*,int /*<<< orphan*/ ) ; 
 int mpt_issue_cfg_req (struct mpt_softc*,TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*) ; 

__attribute__((used)) static int
mpt_user_read_extcfg_header(struct mpt_softc *mpt,
    struct mpt_ext_cfg_page_req *ext_page_req)
{
	request_t  *req;
	cfgparms_t params;
	MSG_CONFIG_REPLY *cfgp;
	int	    error;

	req = mpt_get_request(mpt, TRUE);
	if (req == NULL) {
		mpt_prt(mpt, "mpt_user_read_extcfg_header: Get request failed!\n");
		return (ENOMEM);
	}

	params.Action = MPI_CONFIG_ACTION_PAGE_HEADER;
	params.PageVersion = ext_page_req->header.PageVersion;
	params.PageLength = 0;
	params.PageNumber = ext_page_req->header.PageNumber;
	params.PageType = MPI_CONFIG_PAGETYPE_EXTENDED;
	params.PageAddress = le32toh(ext_page_req->page_address);
	params.ExtPageType = ext_page_req->header.ExtPageType;
	params.ExtPageLength = 0;
	error = mpt_issue_cfg_req(mpt, req, &params, /*addr*/0, /*len*/0,
				  TRUE, 5000);
	if (error != 0) {
		/*
		 * Leave the request. Without resetting the chip, it's
		 * still owned by it and we'll just get into trouble
		 * freeing it now. Mark it as abandoned so that if it
		 * shows up later it can be freed.
		 */
		mpt_prt(mpt, "mpt_user_read_extcfg_header timed out\n");
		return (ETIMEDOUT);
	}

	ext_page_req->ioc_status = htole16(req->IOCStatus);
	if ((req->IOCStatus & MPI_IOCSTATUS_MASK) == MPI_IOCSTATUS_SUCCESS) {
		cfgp = req->req_vbuf;
		ext_page_req->header.PageVersion = cfgp->Header.PageVersion;
		ext_page_req->header.PageNumber = cfgp->Header.PageNumber;
		ext_page_req->header.PageType = cfgp->Header.PageType;
		ext_page_req->header.ExtPageLength = cfgp->ExtPageLength;
		ext_page_req->header.ExtPageType = cfgp->ExtPageType;
	}
	mpt_free_request(mpt, req);
	return (0);
}