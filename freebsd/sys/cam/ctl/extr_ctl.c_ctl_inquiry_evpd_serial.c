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
struct scsi_vpd_unit_serial_number {int device; int length; scalar_t__ serial_num; int /*<<< orphan*/  page_code; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct ctl_scsiio {int /*<<< orphan*/  be_move_done; TYPE_2__ io_hdr; int /*<<< orphan*/  kern_data_len; int /*<<< orphan*/  kern_total_len; scalar_t__ kern_sg_entries; scalar_t__ kern_rel_offset; scalar_t__ kern_data_ptr; } ;
struct ctl_lun {TYPE_1__* be_lun; } ;
struct TYPE_3__ {int lun_type; scalar_t__ serial_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_FLAG_ALLOCATED ; 
 struct ctl_lun* CTL_LUN (struct ctl_scsiio*) ; 
 int CTL_RETVAL_COMPLETE ; 
 int CTL_SN_LEN ; 
 int /*<<< orphan*/  M_CTL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int SID_QUAL_LU_CONNECTED ; 
 int SID_QUAL_LU_OFFLINE ; 
 int /*<<< orphan*/  SVPD_UNIT_SERIAL_NUMBER ; 
 int T_DIRECT ; 
 int /*<<< orphan*/  ctl_config_move_done ; 
 int /*<<< orphan*/  ctl_datamove (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_set_success (struct ctl_scsiio*) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static int
ctl_inquiry_evpd_serial(struct ctl_scsiio *ctsio, int alloc_len)
{
	struct ctl_lun *lun = CTL_LUN(ctsio);
	struct scsi_vpd_unit_serial_number *sn_ptr;
	int data_len;

	data_len = 4 + CTL_SN_LEN;
	ctsio->kern_data_ptr = malloc(data_len, M_CTL, M_WAITOK | M_ZERO);
	sn_ptr = (struct scsi_vpd_unit_serial_number *)ctsio->kern_data_ptr;
	ctsio->kern_rel_offset = 0;
	ctsio->kern_sg_entries = 0;
	ctsio->kern_data_len = min(data_len, alloc_len);
	ctsio->kern_total_len = ctsio->kern_data_len;

	/*
	 * The control device is always connected.  The disk device, on the
	 * other hand, may not be online all the time.  Need to change this
	 * to figure out whether the disk device is actually online or not.
	 */
	if (lun != NULL)
		sn_ptr->device = (SID_QUAL_LU_CONNECTED << 5) |
				  lun->be_lun->lun_type;
	else
		sn_ptr->device = (SID_QUAL_LU_OFFLINE << 5) | T_DIRECT;

	sn_ptr->page_code = SVPD_UNIT_SERIAL_NUMBER;
	sn_ptr->length = CTL_SN_LEN;
	/*
	 * If we don't have a LUN, we just leave the serial number as
	 * all spaces.
	 */
	if (lun != NULL) {
		strncpy((char *)sn_ptr->serial_num,
			(char *)lun->be_lun->serial_num, CTL_SN_LEN);
	} else
		memset(sn_ptr->serial_num, 0x20, CTL_SN_LEN);

	ctl_set_success(ctsio);
	ctsio->io_hdr.flags |= CTL_FLAG_ALLOCATED;
	ctsio->be_move_done = ctl_config_move_done;
	ctl_datamove((union ctl_io *)ctsio);
	return (CTL_RETVAL_COMPLETE);
}