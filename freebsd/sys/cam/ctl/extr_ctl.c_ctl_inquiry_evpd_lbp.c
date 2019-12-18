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
struct scsi_vpd_logical_block_prov {int device; int flags; void* prov_type; int /*<<< orphan*/  threshold_exponent; int /*<<< orphan*/  page_length; int /*<<< orphan*/  page_code; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct ctl_scsiio {int /*<<< orphan*/  be_move_done; TYPE_2__ io_hdr; int /*<<< orphan*/  kern_data_len; int /*<<< orphan*/  kern_total_len; scalar_t__ kern_rel_offset; scalar_t__ kern_sg_entries; scalar_t__ kern_data_ptr; } ;
struct ctl_lun {TYPE_1__* be_lun; } ;
struct TYPE_3__ {int lun_type; int flags; int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_FLAG_ALLOCATED ; 
 int /*<<< orphan*/  CTL_LBP_EXPONENT ; 
 struct ctl_lun* CTL_LUN (struct ctl_scsiio*) ; 
 int CTL_LUN_FLAG_UNMAP ; 
 int CTL_RETVAL_COMPLETE ; 
 int /*<<< orphan*/  M_CTL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int SID_QUAL_LU_CONNECTED ; 
 int SID_QUAL_LU_OFFLINE ; 
 int /*<<< orphan*/  SVPD_LBP ; 
 int SVPD_LBP_ANC_SUP ; 
 void* SVPD_LBP_RESOURCE ; 
 int SVPD_LBP_RZ ; 
 void* SVPD_LBP_THIN ; 
 int SVPD_LBP_UNMAP ; 
 int SVPD_LBP_WS10 ; 
 int SVPD_LBP_WS16 ; 
 int T_DIRECT ; 
 int /*<<< orphan*/  ctl_config_move_done ; 
 int /*<<< orphan*/  ctl_datamove (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_set_success (struct ctl_scsiio*) ; 
 char* dnvlist_get_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  scsi_ulto2b (int,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
ctl_inquiry_evpd_lbp(struct ctl_scsiio *ctsio, int alloc_len)
{
	struct ctl_lun *lun = CTL_LUN(ctsio);
	struct scsi_vpd_logical_block_prov *lbp_ptr;
	const char *value;

	ctsio->kern_data_ptr = malloc(sizeof(*lbp_ptr), M_CTL, M_WAITOK | M_ZERO);
	lbp_ptr = (struct scsi_vpd_logical_block_prov *)ctsio->kern_data_ptr;
	ctsio->kern_sg_entries = 0;
	ctsio->kern_rel_offset = 0;
	ctsio->kern_data_len = min(sizeof(*lbp_ptr), alloc_len);
	ctsio->kern_total_len = ctsio->kern_data_len;

	/*
	 * The control device is always connected.  The disk device, on the
	 * other hand, may not be online all the time.  Need to change this
	 * to figure out whether the disk device is actually online or not.
	 */
	if (lun != NULL)
		lbp_ptr->device = (SID_QUAL_LU_CONNECTED << 5) |
				  lun->be_lun->lun_type;
	else
		lbp_ptr->device = (SID_QUAL_LU_OFFLINE << 5) | T_DIRECT;

	lbp_ptr->page_code = SVPD_LBP;
	scsi_ulto2b(sizeof(*lbp_ptr) - 4, lbp_ptr->page_length);
	lbp_ptr->threshold_exponent = CTL_LBP_EXPONENT;
	if (lun != NULL && lun->be_lun->flags & CTL_LUN_FLAG_UNMAP) {
		lbp_ptr->flags = SVPD_LBP_UNMAP | SVPD_LBP_WS16 |
		    SVPD_LBP_WS10 | SVPD_LBP_RZ | SVPD_LBP_ANC_SUP;
		value = dnvlist_get_string(lun->be_lun->options,
		    "provisioning_type", NULL);
		if (value != NULL) {
			if (strcmp(value, "resource") == 0)
				lbp_ptr->prov_type = SVPD_LBP_RESOURCE;
			else if (strcmp(value, "thin") == 0)
				lbp_ptr->prov_type = SVPD_LBP_THIN;
		} else
			lbp_ptr->prov_type = SVPD_LBP_THIN;
	}

	ctl_set_success(ctsio);
	ctsio->io_hdr.flags |= CTL_FLAG_ALLOCATED;
	ctsio->be_move_done = ctl_config_move_done;
	ctl_datamove((union ctl_io *)ctsio);
	return (CTL_RETVAL_COMPLETE);
}