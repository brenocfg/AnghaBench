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
struct mpt_softc {int dummy; } ;
struct mpt_page_memory {int /*<<< orphan*/  map; int /*<<< orphan*/  tag; int /*<<< orphan*/  paddr; TYPE_3__* vaddr; } ;
struct mpt_ext_cfg_page_req {int /*<<< orphan*/  ioc_status; int /*<<< orphan*/  len; int /*<<< orphan*/  page_address; } ;
struct TYPE_8__ {int IOCStatus; } ;
typedef  TYPE_1__ request_t ;
struct TYPE_9__ {int /*<<< orphan*/  ExtPageLength; int /*<<< orphan*/  ExtPageType; int /*<<< orphan*/  PageAddress; int /*<<< orphan*/  PageType; int /*<<< orphan*/  PageNumber; scalar_t__ PageLength; int /*<<< orphan*/  PageVersion; int /*<<< orphan*/  Action; } ;
typedef  TYPE_2__ cfgparms_t ;
struct TYPE_10__ {int /*<<< orphan*/  ExtPageLength; int /*<<< orphan*/  ExtPageType; int /*<<< orphan*/  PageNumber; int /*<<< orphan*/  PageVersion; } ;
typedef  TYPE_3__ CONFIG_EXTENDED_PAGE_HEADER ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MPI_CONFIG_ACTION_PAGE_READ_CURRENT ; 
 int /*<<< orphan*/  MPI_CONFIG_PAGETYPE_EXTENDED ; 
 int MPI_IOCSTATUS_MASK ; 
 int MPI_IOCSTATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  htole16 (int) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_free_request (struct mpt_softc*,TYPE_1__*) ; 
 TYPE_1__* mpt_get_request (struct mpt_softc*,int /*<<< orphan*/ ) ; 
 int mpt_issue_cfg_req (struct mpt_softc*,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*) ; 

__attribute__((used)) static int
mpt_user_read_extcfg_page(struct mpt_softc *mpt,
    struct mpt_ext_cfg_page_req *ext_page_req, struct mpt_page_memory *mpt_page)
{
	CONFIG_EXTENDED_PAGE_HEADER *hdr;
	request_t    *req;
	cfgparms_t    params;
	int	      error;

	req = mpt_get_request(mpt, TRUE);
	if (req == NULL) {
		mpt_prt(mpt, "mpt_user_read_extcfg_page: Get request failed!\n");
		return (ENOMEM);
	}

	hdr = mpt_page->vaddr;
	params.Action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;
	params.PageVersion = hdr->PageVersion;
	params.PageLength = 0;
	params.PageNumber = hdr->PageNumber;
	params.PageType = MPI_CONFIG_PAGETYPE_EXTENDED;
	params.PageAddress = le32toh(ext_page_req->page_address);
	params.ExtPageType = hdr->ExtPageType;
	params.ExtPageLength = hdr->ExtPageLength;
	bus_dmamap_sync(mpt_page->tag, mpt_page->map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
	error = mpt_issue_cfg_req(mpt, req, &params, mpt_page->paddr,
	    le32toh(ext_page_req->len), TRUE, 5000);
	if (error != 0) {
		mpt_prt(mpt, "mpt_user_read_extcfg_page timed out\n");
		return (ETIMEDOUT);
	}

	ext_page_req->ioc_status = htole16(req->IOCStatus);
	if ((req->IOCStatus & MPI_IOCSTATUS_MASK) == MPI_IOCSTATUS_SUCCESS)
		bus_dmamap_sync(mpt_page->tag, mpt_page->map,
		    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
	mpt_free_request(mpt, req);
	return (0);
}