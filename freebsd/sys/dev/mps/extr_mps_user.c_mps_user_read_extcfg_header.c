#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mps_softc {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  ExtPageType; scalar_t__ ExtPageLength; int /*<<< orphan*/  PageType; int /*<<< orphan*/  PageNumber; int /*<<< orphan*/  PageVersion; } ;
struct mps_ext_cfg_page_req {int ioc_status; TYPE_2__ header; int /*<<< orphan*/  page_address; } ;
struct TYPE_6__ {int /*<<< orphan*/  ExtPageType; scalar_t__ ExtPageLength; int /*<<< orphan*/  PageType; int /*<<< orphan*/  PageNumber; int /*<<< orphan*/  PageVersion; } ;
struct TYPE_4__ {TYPE_3__ Ext; } ;
struct mps_config_params {int /*<<< orphan*/  status; int /*<<< orphan*/ * callback; scalar_t__ length; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  page_address; int /*<<< orphan*/  action; TYPE_1__ hdr; } ;
typedef  TYPE_3__ MPI2_CONFIG_EXTENDED_PAGE_HEADER ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MPI2_CONFIG_ACTION_PAGE_HEADER ; 
 int /*<<< orphan*/  MPI2_CONFIG_PAGETYPE_EXTENDED ; 
 int MPI2_IOCSTATUS_MASK ; 
 int MPI2_IOCSTATUS_SUCCESS ; 
 int htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mps_printf (struct mps_softc*,char*) ; 
 int mps_read_config_page (struct mps_softc*,struct mps_config_params*) ; 

__attribute__((used)) static int
mps_user_read_extcfg_header(struct mps_softc *sc,
    struct mps_ext_cfg_page_req *ext_page_req)
{
	MPI2_CONFIG_EXTENDED_PAGE_HEADER *hdr;
	struct mps_config_params params;
	int	    error;

	hdr = &params.hdr.Ext;
	params.action = MPI2_CONFIG_ACTION_PAGE_HEADER;
	hdr->PageVersion = ext_page_req->header.PageVersion;
	hdr->PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	hdr->ExtPageLength = 0;
	hdr->PageNumber = ext_page_req->header.PageNumber;
	hdr->ExtPageType = ext_page_req->header.ExtPageType;
	params.page_address = le32toh(ext_page_req->page_address);
	params.buffer = NULL;
	params.length = 0;
	params.callback = NULL;

	if ((error = mps_read_config_page(sc, &params)) != 0) {
		/*
		 * Leave the request. Without resetting the chip, it's
		 * still owned by it and we'll just get into trouble
		 * freeing it now. Mark it as abandoned so that if it
		 * shows up later it can be freed.
		 */
		mps_printf(sc, "mps_user_read_extcfg_header timed out\n");
		return (ETIMEDOUT);
	}

	ext_page_req->ioc_status = htole16(params.status);
	if ((ext_page_req->ioc_status & MPI2_IOCSTATUS_MASK) ==
	    MPI2_IOCSTATUS_SUCCESS) {
		ext_page_req->header.PageVersion = hdr->PageVersion;
		ext_page_req->header.PageNumber = hdr->PageNumber;
		ext_page_req->header.PageType = hdr->PageType;
		ext_page_req->header.ExtPageLength = hdr->ExtPageLength;
		ext_page_req->header.ExtPageType = hdr->ExtPageType;
	}

	return (0);
}