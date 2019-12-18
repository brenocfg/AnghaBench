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
struct scsi_vpd_supported_pages {int device; int length; int /*<<< orphan*/ * page_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct ctl_scsiio {int /*<<< orphan*/  be_move_done; TYPE_2__ io_hdr; int /*<<< orphan*/  kern_data_len; int /*<<< orphan*/  kern_total_len; scalar_t__ kern_sg_entries; scalar_t__ kern_rel_offset; scalar_t__ kern_data_ptr; } ;
struct ctl_lun {TYPE_1__* be_lun; } ;
struct TYPE_3__ {int lun_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_FLAG_ALLOCATED ; 
 struct ctl_lun* CTL_LUN (struct ctl_scsiio*) ; 
 int CTL_RETVAL_COMPLETE ; 
 int /*<<< orphan*/  M_CTL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int SCSI_EVPD_NUM_SUPPORTED_PAGES ; 
 int SID_QUAL_LU_CONNECTED ; 
 int SID_QUAL_LU_OFFLINE ; 
 int /*<<< orphan*/  SVPD_BDC ; 
 int /*<<< orphan*/  SVPD_BLOCK_LIMITS ; 
 int /*<<< orphan*/  SVPD_DEVICE_ID ; 
 int /*<<< orphan*/  SVPD_EXTENDED_INQUIRY_DATA ; 
 int /*<<< orphan*/  SVPD_LBP ; 
 int /*<<< orphan*/  SVPD_MODE_PAGE_POLICY ; 
 int /*<<< orphan*/  SVPD_SCSI_PORTS ; 
 int /*<<< orphan*/  SVPD_SCSI_SFS ; 
 int /*<<< orphan*/  SVPD_SCSI_TPC ; 
 int /*<<< orphan*/  SVPD_SUPPORTED_PAGES ; 
 int /*<<< orphan*/  SVPD_UNIT_SERIAL_NUMBER ; 
 int T_DIRECT ; 
 int /*<<< orphan*/  ctl_config_move_done ; 
 int /*<<< orphan*/  ctl_datamove (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_set_success (struct ctl_scsiio*) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,int) ; 

__attribute__((used)) static int
ctl_inquiry_evpd_supported(struct ctl_scsiio *ctsio, int alloc_len)
{
	struct ctl_lun *lun = CTL_LUN(ctsio);
	struct scsi_vpd_supported_pages *pages;
	int sup_page_size;
	int p;

	sup_page_size = sizeof(struct scsi_vpd_supported_pages) *
	    SCSI_EVPD_NUM_SUPPORTED_PAGES;
	ctsio->kern_data_ptr = malloc(sup_page_size, M_CTL, M_WAITOK | M_ZERO);
	pages = (struct scsi_vpd_supported_pages *)ctsio->kern_data_ptr;
	ctsio->kern_rel_offset = 0;
	ctsio->kern_sg_entries = 0;
	ctsio->kern_data_len = min(sup_page_size, alloc_len);
	ctsio->kern_total_len = ctsio->kern_data_len;

	/*
	 * The control device is always connected.  The disk device, on the
	 * other hand, may not be online all the time.  Need to change this
	 * to figure out whether the disk device is actually online or not.
	 */
	if (lun != NULL)
		pages->device = (SID_QUAL_LU_CONNECTED << 5) |
				lun->be_lun->lun_type;
	else
		pages->device = (SID_QUAL_LU_OFFLINE << 5) | T_DIRECT;

	p = 0;
	/* Supported VPD pages */
	pages->page_list[p++] = SVPD_SUPPORTED_PAGES;
	/* Serial Number */
	pages->page_list[p++] = SVPD_UNIT_SERIAL_NUMBER;
	/* Device Identification */
	pages->page_list[p++] = SVPD_DEVICE_ID;
	/* Extended INQUIRY Data */
	pages->page_list[p++] = SVPD_EXTENDED_INQUIRY_DATA;
	/* Mode Page Policy */
	pages->page_list[p++] = SVPD_MODE_PAGE_POLICY;
	/* SCSI Ports */
	pages->page_list[p++] = SVPD_SCSI_PORTS;
	/* Third-party Copy */
	pages->page_list[p++] = SVPD_SCSI_TPC;
	/* SCSI Feature Sets */
	pages->page_list[p++] = SVPD_SCSI_SFS;
	if (lun != NULL && lun->be_lun->lun_type == T_DIRECT) {
		/* Block limits */
		pages->page_list[p++] = SVPD_BLOCK_LIMITS;
		/* Block Device Characteristics */
		pages->page_list[p++] = SVPD_BDC;
		/* Logical Block Provisioning */
		pages->page_list[p++] = SVPD_LBP;
	}
	pages->length = p;

	ctl_set_success(ctsio);
	ctsio->io_hdr.flags |= CTL_FLAG_ALLOCATED;
	ctsio->be_move_done = ctl_config_move_done;
	ctl_datamove((union ctl_io *)ctsio);
	return (CTL_RETVAL_COMPLETE);
}