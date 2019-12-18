#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct mpr_softc {int mpr_flags; } ;
struct TYPE_13__ {scalar_t__ PageType; int /*<<< orphan*/  PageVersion; scalar_t__ PageLength; int /*<<< orphan*/  PageNumber; } ;
struct TYPE_14__ {int /*<<< orphan*/  PageVersion; int /*<<< orphan*/  PageNumber; int /*<<< orphan*/  ExtPageLength; int /*<<< orphan*/  ExtPageType; } ;
struct TYPE_8__ {TYPE_6__ Struct; TYPE_7__ Ext; } ;
struct mpr_config_params {int /*<<< orphan*/ * callback; int /*<<< orphan*/  length; int /*<<< orphan*/ * buffer; TYPE_1__ hdr; int /*<<< orphan*/  page_address; int /*<<< orphan*/  action; } ;
struct TYPE_10__ {int /*<<< orphan*/  RequestFlags; } ;
struct TYPE_11__ {TYPE_3__ Default; } ;
struct mpr_command {int cm_sglsize; int cm_flags; int /*<<< orphan*/  (* cm_complete ) (struct mpr_softc*,struct mpr_command*) ;struct mpr_config_params* cm_complete_data; TYPE_4__ cm_desc; int /*<<< orphan*/ * cm_sge; int /*<<< orphan*/ * cm_data; int /*<<< orphan*/  cm_length; scalar_t__ cm_req; } ;
struct TYPE_9__ {scalar_t__ PageType; int /*<<< orphan*/  PageVersion; scalar_t__ PageLength; int /*<<< orphan*/  PageNumber; } ;
struct TYPE_12__ {int /*<<< orphan*/  PageBufferSGE; TYPE_2__ Header; int /*<<< orphan*/  ExtPageLength; int /*<<< orphan*/  ExtPageType; int /*<<< orphan*/  PageAddress; scalar_t__ ChainOffset; scalar_t__ SGLFlags; int /*<<< orphan*/  Action; int /*<<< orphan*/  Function; } ;
typedef  int /*<<< orphan*/  MPI2_SGE_IO_UNION ;
typedef  TYPE_5__ MPI2_CONFIG_REQUEST ;
typedef  TYPE_6__ MPI2_CONFIG_PAGE_HEADER ;
typedef  TYPE_7__ MPI2_CONFIG_EXTENDED_PAGE_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_SLEEP ; 
 int EBUSY ; 
 scalar_t__ MPI2_CONFIG_PAGETYPE_EXTENDED ; 
 int /*<<< orphan*/  MPI2_FUNCTION_CONFIG ; 
 int /*<<< orphan*/  MPI2_REQ_DESCRIPT_FLAGS_DEFAULT_TYPE ; 
 int MPR_CM_FLAGS_DATAIN ; 
 int MPR_CM_FLAGS_SGE_SIMPLE ; 
 int /*<<< orphan*/  MPR_FAULT ; 
 int MPR_FLAGS_BUSY ; 
 struct mpr_command* mpr_alloc_command (struct mpr_softc*) ; 
 int /*<<< orphan*/  mpr_config_complete (struct mpr_softc*,struct mpr_command*) ; 
 int /*<<< orphan*/  mpr_dprint (struct mpr_softc*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mpr_free_command (struct mpr_softc*,struct mpr_command*) ; 
 int mpr_map_command (struct mpr_softc*,struct mpr_command*) ; 
 int mpr_wait_command (struct mpr_softc*,struct mpr_command**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
mpr_read_config_page(struct mpr_softc *sc, struct mpr_config_params *params)
{
	MPI2_CONFIG_REQUEST *req;
	struct mpr_command *cm;
	int error;

	if (sc->mpr_flags & MPR_FLAGS_BUSY) {
		return (EBUSY);
	}

	cm = mpr_alloc_command(sc);
	if (cm == NULL) {
		return (EBUSY);
	}

	req = (MPI2_CONFIG_REQUEST *)cm->cm_req;
	req->Function = MPI2_FUNCTION_CONFIG;
	req->Action = params->action;
	req->SGLFlags = 0;
	req->ChainOffset = 0;
	req->PageAddress = params->page_address;
	if (params->hdr.Struct.PageType == MPI2_CONFIG_PAGETYPE_EXTENDED) {
		MPI2_CONFIG_EXTENDED_PAGE_HEADER *hdr;

		hdr = &params->hdr.Ext;
		req->ExtPageType = hdr->ExtPageType;
		req->ExtPageLength = hdr->ExtPageLength;
		req->Header.PageType = MPI2_CONFIG_PAGETYPE_EXTENDED;
		req->Header.PageLength = 0; /* Must be set to zero */
		req->Header.PageNumber = hdr->PageNumber;
		req->Header.PageVersion = hdr->PageVersion;
	} else {
		MPI2_CONFIG_PAGE_HEADER *hdr;

		hdr = &params->hdr.Struct;
		req->Header.PageType = hdr->PageType;
		req->Header.PageNumber = hdr->PageNumber;
		req->Header.PageLength = hdr->PageLength;
		req->Header.PageVersion = hdr->PageVersion;
	}

	cm->cm_data = params->buffer;
	cm->cm_length = params->length;
	if (cm->cm_data != NULL) {
		cm->cm_sge = &req->PageBufferSGE;
		cm->cm_sglsize = sizeof(MPI2_SGE_IO_UNION);
		cm->cm_flags = MPR_CM_FLAGS_SGE_SIMPLE | MPR_CM_FLAGS_DATAIN;
	} else
		cm->cm_sge = NULL;
	cm->cm_desc.Default.RequestFlags = MPI2_REQ_DESCRIPT_FLAGS_DEFAULT_TYPE;

	cm->cm_complete_data = params;
	if (params->callback != NULL) {
		cm->cm_complete = mpr_config_complete;
		return (mpr_map_command(sc, cm));
	} else {
		error = mpr_wait_command(sc, &cm, 0, CAN_SLEEP);
		if (error) {
			mpr_dprint(sc, MPR_FAULT,
			    "Error %d reading config page\n", error);
			if (cm != NULL)
				mpr_free_command(sc, cm);
			return (error);
		}
		mpr_config_complete(sc, cm);
	}

	return (0);
}