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
typedef  int u_int ;
struct mpt_softc {int dummy; } ;
struct mpt_page_memory {int /*<<< orphan*/  map; int /*<<< orphan*/  tag; int /*<<< orphan*/  paddr; TYPE_3__* vaddr; } ;
struct mpt_cfg_page_req {int /*<<< orphan*/  ioc_status; int /*<<< orphan*/  len; int /*<<< orphan*/  page_address; } ;
struct TYPE_8__ {int /*<<< orphan*/  IOCStatus; } ;
typedef  TYPE_1__ request_t ;
struct TYPE_9__ {int PageType; int /*<<< orphan*/  PageAddress; int /*<<< orphan*/  PageNumber; int /*<<< orphan*/  PageLength; int /*<<< orphan*/  PageVersion; int /*<<< orphan*/  Action; } ;
typedef  TYPE_2__ cfgparms_t ;
struct TYPE_10__ {int PageType; int /*<<< orphan*/  PageNumber; int /*<<< orphan*/  PageLength; int /*<<< orphan*/  PageVersion; } ;
typedef  TYPE_3__ CONFIG_PAGE_HEADER ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MPI_CONFIG_ACTION_PAGE_WRITE_CURRENT ; 
 int MPI_CONFIG_PAGEATTR_CHANGEABLE ; 
 int MPI_CONFIG_PAGEATTR_MASK ; 
 int MPI_CONFIG_PAGEATTR_PERSISTENT ; 
 int MPI_CONFIG_PAGETYPE_MASK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_free_request (struct mpt_softc*,TYPE_1__*) ; 
 TYPE_1__* mpt_get_request (struct mpt_softc*,int /*<<< orphan*/ ) ; 
 int mpt_issue_cfg_req (struct mpt_softc*,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*,...) ; 

__attribute__((used)) static int
mpt_user_write_cfg_page(struct mpt_softc *mpt,
    struct mpt_cfg_page_req *page_req, struct mpt_page_memory *mpt_page)
{
	CONFIG_PAGE_HEADER *hdr;
	request_t    *req;
	cfgparms_t    params;
	u_int	      hdr_attr;
	int	      error;

	hdr = mpt_page->vaddr;
	hdr_attr = hdr->PageType & MPI_CONFIG_PAGEATTR_MASK;
	if (hdr_attr != MPI_CONFIG_PAGEATTR_CHANGEABLE &&
	    hdr_attr != MPI_CONFIG_PAGEATTR_PERSISTENT) {
		mpt_prt(mpt, "page type 0x%x not changeable\n",
			hdr->PageType & MPI_CONFIG_PAGETYPE_MASK);
		return (EINVAL);
	}

#if	0
	/*
	 * We shouldn't mask off other bits here.
	 */
	hdr->PageType &= ~MPI_CONFIG_PAGETYPE_MASK;
#endif

	req = mpt_get_request(mpt, TRUE);
	if (req == NULL)
		return (ENOMEM);

	bus_dmamap_sync(mpt_page->tag, mpt_page->map, BUS_DMASYNC_PREREAD |
	    BUS_DMASYNC_PREWRITE);

	/*
	 * There isn't any point in restoring stripped out attributes
	 * if you then mask them going down to issue the request.
	 */

	params.Action = MPI_CONFIG_ACTION_PAGE_WRITE_CURRENT;
	params.PageVersion = hdr->PageVersion;
	params.PageLength = hdr->PageLength;
	params.PageNumber = hdr->PageNumber;
	params.PageAddress = le32toh(page_req->page_address);
#if	0
	/* Restore stripped out attributes */
	hdr->PageType |= hdr_attr;
	params.PageType = hdr->PageType & MPI_CONFIG_PAGETYPE_MASK;
#else
	params.PageType = hdr->PageType;
#endif
	error = mpt_issue_cfg_req(mpt, req, &params, mpt_page->paddr,
	    le32toh(page_req->len), TRUE, 5000);
	if (error != 0) {
		mpt_prt(mpt, "mpt_write_cfg_page timed out\n");
		return (ETIMEDOUT);
	}

	page_req->ioc_status = htole16(req->IOCStatus);
	bus_dmamap_sync(mpt_page->tag, mpt_page->map, BUS_DMASYNC_POSTREAD |
	    BUS_DMASYNC_POSTWRITE);
	mpt_free_request(mpt, req);
	return (0);
}