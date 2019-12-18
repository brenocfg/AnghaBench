#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mps_softc {int dummy; } ;
struct mps_ext_cfg_page_req {int /*<<< orphan*/  ioc_status; int /*<<< orphan*/  len; int /*<<< orphan*/  page_address; } ;
struct TYPE_4__ {int /*<<< orphan*/  ExtPageLength; int /*<<< orphan*/  ExtPageType; int /*<<< orphan*/  PageNumber; int /*<<< orphan*/  PageType; int /*<<< orphan*/  PageVersion; } ;
struct TYPE_3__ {TYPE_2__ Ext; } ;
struct mps_config_params {int /*<<< orphan*/  status; int /*<<< orphan*/ * callback; void* length; void* buffer; void* page_address; int /*<<< orphan*/  action; TYPE_1__ hdr; } ;
typedef  TYPE_2__ MPI2_CONFIG_EXTENDED_PAGE_HEADER ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MPI2_CONFIG_ACTION_PAGE_READ_CURRENT ; 
 int /*<<< orphan*/  MPI2_CONFIG_PAGETYPE_EXTENDED ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 void* le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mps_printf (struct mps_softc*,char*) ; 
 int mps_read_config_page (struct mps_softc*,struct mps_config_params*) ; 

__attribute__((used)) static int
mps_user_read_extcfg_page(struct mps_softc *sc,
    struct mps_ext_cfg_page_req *ext_page_req, void *buf)
{
	MPI2_CONFIG_EXTENDED_PAGE_HEADER *reqhdr, *hdr;
	struct mps_config_params params;
	int error;

	reqhdr = buf;
	hdr = &params.hdr.Ext;
	params.action = MPI2_CONFIG_ACTION_PAGE_READ_CURRENT;
	params.page_address = le32toh(ext_page_req->page_address);
	hdr->PageVersion = reqhdr->PageVersion;
	hdr->PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
	hdr->PageNumber = reqhdr->PageNumber;
	hdr->ExtPageType = reqhdr->ExtPageType;
	hdr->ExtPageLength = reqhdr->ExtPageLength;
	params.buffer = buf;
	params.length = le32toh(ext_page_req->len);
	params.callback = NULL;

	if ((error = mps_read_config_page(sc, &params)) != 0) {
		mps_printf(sc, "mps_user_read_extcfg_page timed out\n");
		return (ETIMEDOUT);
	}

	ext_page_req->ioc_status = htole16(params.status);
	return (0);
}