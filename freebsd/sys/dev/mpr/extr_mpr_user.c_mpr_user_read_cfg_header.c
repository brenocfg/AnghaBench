#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mpr_softc {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  PageType; int /*<<< orphan*/  PageNumber; scalar_t__ PageLength; scalar_t__ PageVersion; } ;
struct TYPE_5__ {TYPE_2__ Struct; } ;
struct mpr_config_params {int /*<<< orphan*/  status; int /*<<< orphan*/ * callback; scalar_t__ length; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  page_address; int /*<<< orphan*/  action; TYPE_1__ hdr; } ;
struct TYPE_7__ {int /*<<< orphan*/  PageType; int /*<<< orphan*/  PageNumber; } ;
struct mpr_cfg_page_req {int ioc_status; TYPE_4__ header; int /*<<< orphan*/  page_address; } ;
typedef  TYPE_2__ MPI2_CONFIG_PAGE_HEADER ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MPI2_CONFIG_ACTION_PAGE_HEADER ; 
 int MPI2_IOCSTATUS_MASK ; 
 int MPI2_IOCSTATUS_SUCCESS ; 
 int /*<<< orphan*/  bcopy (TYPE_2__*,TYPE_4__*,int) ; 
 int htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpr_printf (struct mpr_softc*,char*) ; 
 int mpr_read_config_page (struct mpr_softc*,struct mpr_config_params*) ; 

__attribute__((used)) static int
mpr_user_read_cfg_header(struct mpr_softc *sc,
    struct mpr_cfg_page_req *page_req)
{
	MPI2_CONFIG_PAGE_HEADER *hdr;
	struct mpr_config_params params;
	int	    error;

	hdr = &params.hdr.Struct;
	params.action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	params.page_address = le32toh(page_req->page_address);
	hdr->PageVersion = 0;
	hdr->PageLength = 0;
	hdr->PageNumber = page_req->header.PageNumber;
	hdr->PageType = page_req->header.PageType;
	params.buffer = NULL;
	params.length = 0;
	params.callback = NULL;

	if ((error = mpr_read_config_page(sc, &params)) != 0) {
		/*
		 * Leave the request. Without resetting the chip, it's
		 * still owned by it and we'll just get into trouble
		 * freeing it now. Mark it as abandoned so that if it
		 * shows up later it can be freed.
		 */
		mpr_printf(sc, "read_cfg_header timed out\n");
		return (ETIMEDOUT);
	}

	page_req->ioc_status = htole16(params.status);
	if ((page_req->ioc_status & MPI2_IOCSTATUS_MASK) ==
	    MPI2_IOCSTATUS_SUCCESS) {
		bcopy(hdr, &page_req->header, sizeof(page_req->header));
	}

	return (0);
}