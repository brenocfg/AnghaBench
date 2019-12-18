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
typedef  int u_int ;
struct scsi_vpd_block_device_characteristics {int device; int wab_wac_ff; int flags; int /*<<< orphan*/  medium_rotation_rate; int /*<<< orphan*/  page_length; int /*<<< orphan*/  page_code; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct ctl_scsiio {int /*<<< orphan*/  be_move_done; TYPE_2__ io_hdr; int /*<<< orphan*/  kern_data_len; int /*<<< orphan*/  kern_total_len; scalar_t__ kern_rel_offset; scalar_t__ kern_sg_entries; scalar_t__ kern_data_ptr; } ;
struct ctl_lun {TYPE_1__* be_lun; } ;
struct TYPE_3__ {int lun_type; int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int CTL_DEFAULT_ROTATION_RATE ; 
 int /*<<< orphan*/  CTL_FLAG_ALLOCATED ; 
 struct ctl_lun* CTL_LUN (struct ctl_scsiio*) ; 
 int CTL_RETVAL_COMPLETE ; 
 int /*<<< orphan*/  M_CTL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int SID_QUAL_LU_CONNECTED ; 
 int SID_QUAL_LU_OFFLINE ; 
 int /*<<< orphan*/  SVPD_BDC ; 
 int SVPD_FUAB ; 
 int SVPD_RBWZ ; 
 int SVPD_VBULS ; 
 int T_DIRECT ; 
 int /*<<< orphan*/  ctl_config_move_done ; 
 int /*<<< orphan*/  ctl_datamove (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_set_success (struct ctl_scsiio*) ; 
 char* dnvlist_get_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  scsi_ulto2b (int,int /*<<< orphan*/ ) ; 
 int strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ctl_inquiry_evpd_bdc(struct ctl_scsiio *ctsio, int alloc_len)
{
	struct ctl_lun *lun = CTL_LUN(ctsio);
	struct scsi_vpd_block_device_characteristics *bdc_ptr;
	const char *value;
	u_int i;

	ctsio->kern_data_ptr = malloc(sizeof(*bdc_ptr), M_CTL, M_WAITOK | M_ZERO);
	bdc_ptr = (struct scsi_vpd_block_device_characteristics *)ctsio->kern_data_ptr;
	ctsio->kern_sg_entries = 0;
	ctsio->kern_rel_offset = 0;
	ctsio->kern_data_len = min(sizeof(*bdc_ptr), alloc_len);
	ctsio->kern_total_len = ctsio->kern_data_len;

	/*
	 * The control device is always connected.  The disk device, on the
	 * other hand, may not be online all the time.  Need to change this
	 * to figure out whether the disk device is actually online or not.
	 */
	if (lun != NULL)
		bdc_ptr->device = (SID_QUAL_LU_CONNECTED << 5) |
				  lun->be_lun->lun_type;
	else
		bdc_ptr->device = (SID_QUAL_LU_OFFLINE << 5) | T_DIRECT;
	bdc_ptr->page_code = SVPD_BDC;
	scsi_ulto2b(sizeof(*bdc_ptr) - 4, bdc_ptr->page_length);
	if (lun != NULL &&
	    (value = dnvlist_get_string(lun->be_lun->options, "rpm", NULL)) != NULL)
		i = strtol(value, NULL, 0);
	else
		i = CTL_DEFAULT_ROTATION_RATE;
	scsi_ulto2b(i, bdc_ptr->medium_rotation_rate);
	if (lun != NULL &&
	    (value = dnvlist_get_string(lun->be_lun->options, "formfactor", NULL)) != NULL)
		i = strtol(value, NULL, 0);
	else
		i = 0;
	bdc_ptr->wab_wac_ff = (i & 0x0f);
	bdc_ptr->flags = SVPD_RBWZ | SVPD_FUAB | SVPD_VBULS;

	ctl_set_success(ctsio);
	ctsio->io_hdr.flags |= CTL_FLAG_ALLOCATED;
	ctsio->be_move_done = ctl_config_move_done;
	ctl_datamove((union ctl_io *)ctsio);
	return (CTL_RETVAL_COMPLETE);
}