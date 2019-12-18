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
typedef  union ctl_io {int dummy; } ctl_io ;
struct scsi_log_sense {int page; int subpage; int /*<<< orphan*/  length; } ;
struct scsi_log_header {int page; int subpage; int /*<<< orphan*/  datalen; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct ctl_scsiio {int /*<<< orphan*/  be_move_done; TYPE_2__ io_hdr; scalar_t__ kern_data_ptr; int /*<<< orphan*/  kern_data_len; int /*<<< orphan*/  kern_total_len; scalar_t__ kern_rel_offset; scalar_t__ kern_sg_entries; scalar_t__ cdb; } ;
struct ctl_page_index {int page_code; int subpage; int page_len; int /*<<< orphan*/  page_data; int /*<<< orphan*/  (* sense_handler ) (struct ctl_scsiio*,struct ctl_page_index*,int) ;} ;
struct TYPE_3__ {struct ctl_page_index* index; } ;
struct ctl_lun {TYPE_1__ log_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DEBUG_PRINT (char*) ; 
 int /*<<< orphan*/  CTL_FLAG_ALLOCATED ; 
 struct ctl_lun* CTL_LUN (struct ctl_scsiio*) ; 
 int CTL_NUM_LOG_PAGES ; 
 int CTL_RETVAL_COMPLETE ; 
 int /*<<< orphan*/  M_CTL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int SLS_LOGICAL_BLOCK_PROVISIONING ; 
 int SLS_PAGE_CODE ; 
 int SLS_PAGE_CTRL_MASK ; 
 int SL_DS ; 
 int SL_PAGE_CODE ; 
 int SL_SPF ; 
 int /*<<< orphan*/  ctl_config_move_done ; 
 int /*<<< orphan*/  ctl_datamove (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_set_invalid_field (struct ctl_scsiio*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_set_success (struct ctl_scsiio*) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct scsi_log_header*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int scsi_2btoul (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto2b (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ctl_scsiio*,struct ctl_page_index*,int) ; 

int
ctl_log_sense(struct ctl_scsiio *ctsio)
{
	struct ctl_lun *lun = CTL_LUN(ctsio);
	int i, pc, page_code, subpage;
	int alloc_len, total_len;
	struct ctl_page_index *page_index;
	struct scsi_log_sense *cdb;
	struct scsi_log_header *header;

	CTL_DEBUG_PRINT(("ctl_log_sense\n"));

	cdb = (struct scsi_log_sense *)ctsio->cdb;
	pc = (cdb->page & SLS_PAGE_CTRL_MASK) >> 6;
	page_code = cdb->page & SLS_PAGE_CODE;
	subpage = cdb->subpage;
	alloc_len = scsi_2btoul(cdb->length);

	page_index = NULL;
	for (i = 0; i < CTL_NUM_LOG_PAGES; i++) {
		page_index = &lun->log_pages.index[i];

		/* Look for the right page code */
		if ((page_index->page_code & SL_PAGE_CODE) != page_code)
			continue;

		/* Look for the right subpage or the subpage wildcard*/
		if (page_index->subpage != subpage)
			continue;

		break;
	}
	if (i >= CTL_NUM_LOG_PAGES) {
		ctl_set_invalid_field(ctsio,
				      /*sks_valid*/ 1,
				      /*command*/ 1,
				      /*field*/ 2,
				      /*bit_valid*/ 0,
				      /*bit*/ 0);
		ctl_done((union ctl_io *)ctsio);
		return (CTL_RETVAL_COMPLETE);
	}

	total_len = sizeof(struct scsi_log_header) + page_index->page_len;

	ctsio->kern_data_ptr = malloc(total_len, M_CTL, M_WAITOK | M_ZERO);
	ctsio->kern_sg_entries = 0;
	ctsio->kern_rel_offset = 0;
	ctsio->kern_data_len = min(total_len, alloc_len);
	ctsio->kern_total_len = ctsio->kern_data_len;

	header = (struct scsi_log_header *)ctsio->kern_data_ptr;
	header->page = page_index->page_code;
	if (page_index->page_code == SLS_LOGICAL_BLOCK_PROVISIONING)
		header->page |= SL_DS;
	if (page_index->subpage) {
		header->page |= SL_SPF;
		header->subpage = page_index->subpage;
	}
	scsi_ulto2b(page_index->page_len, header->datalen);

	/*
	 * Call the handler, if it exists, to update the
	 * page to the latest values.
	 */
	if (page_index->sense_handler != NULL)
		page_index->sense_handler(ctsio, page_index, pc);

	memcpy(header + 1, page_index->page_data, page_index->page_len);

	ctl_set_success(ctsio);
	ctsio->io_hdr.flags |= CTL_FLAG_ALLOCATED;
	ctsio->be_move_done = ctl_config_move_done;
	ctl_datamove((union ctl_io *)ctsio);
	return (CTL_RETVAL_COMPLETE);
}