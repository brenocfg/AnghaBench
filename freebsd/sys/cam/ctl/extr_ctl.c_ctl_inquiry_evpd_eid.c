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
struct scsi_vpd_extended_inquiry_data {int device; int flags2; scalar_t__ max_sense_length; int /*<<< orphan*/  flags5; int /*<<< orphan*/  flags4; int /*<<< orphan*/  flags3; int /*<<< orphan*/  page_length; int /*<<< orphan*/  page_code; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct ctl_scsiio {int /*<<< orphan*/  be_move_done; TYPE_2__ io_hdr; int /*<<< orphan*/  kern_data_len; int /*<<< orphan*/  kern_total_len; scalar_t__ kern_rel_offset; scalar_t__ kern_sg_entries; scalar_t__ kern_data_ptr; } ;
struct ctl_lun {TYPE_1__* be_lun; } ;
struct TYPE_3__ {int lun_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_FLAG_ALLOCATED ; 
 struct ctl_lun* CTL_LUN (struct ctl_scsiio*) ; 
 int CTL_RETVAL_COMPLETE ; 
 int /*<<< orphan*/  M_CTL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int SID_QUAL_LU_CONNECTED ; 
 int SID_QUAL_LU_OFFLINE ; 
 int SVPD_EID_HEADSUP ; 
 int /*<<< orphan*/  SVPD_EID_LUICLR ; 
 int SVPD_EID_ORDSUP ; 
 int /*<<< orphan*/  SVPD_EID_RTD_SUP ; 
 int SVPD_EID_SIMPSUP ; 
 int /*<<< orphan*/  SVPD_EID_V_SUP ; 
 int /*<<< orphan*/  SVPD_EXTENDED_INQUIRY_DATA ; 
 int T_DIRECT ; 
 int /*<<< orphan*/  ctl_config_move_done ; 
 int /*<<< orphan*/  ctl_datamove (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_set_success (struct ctl_scsiio*) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  scsi_ulto2b (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ctl_inquiry_evpd_eid(struct ctl_scsiio *ctsio, int alloc_len)
{
	struct ctl_lun *lun = CTL_LUN(ctsio);
	struct scsi_vpd_extended_inquiry_data *eid_ptr;
	int data_len;

	data_len = sizeof(struct scsi_vpd_extended_inquiry_data);
	ctsio->kern_data_ptr = malloc(data_len, M_CTL, M_WAITOK | M_ZERO);
	eid_ptr = (struct scsi_vpd_extended_inquiry_data *)ctsio->kern_data_ptr;
	ctsio->kern_sg_entries = 0;
	ctsio->kern_rel_offset = 0;
	ctsio->kern_data_len = min(data_len, alloc_len);
	ctsio->kern_total_len = ctsio->kern_data_len;

	/*
	 * The control device is always connected.  The disk device, on the
	 * other hand, may not be online all the time.
	 */
	if (lun != NULL)
		eid_ptr->device = (SID_QUAL_LU_CONNECTED << 5) |
				     lun->be_lun->lun_type;
	else
		eid_ptr->device = (SID_QUAL_LU_OFFLINE << 5) | T_DIRECT;
	eid_ptr->page_code = SVPD_EXTENDED_INQUIRY_DATA;
	scsi_ulto2b(data_len - 4, eid_ptr->page_length);
	/*
	 * We support head of queue, ordered and simple tags.
	 */
	eid_ptr->flags2 = SVPD_EID_HEADSUP | SVPD_EID_ORDSUP | SVPD_EID_SIMPSUP;
	/*
	 * Volatile cache supported.
	 */
	eid_ptr->flags3 = SVPD_EID_V_SUP;

	/*
	 * This means that we clear the REPORTED LUNS DATA HAS CHANGED unit
	 * attention for a particular IT nexus on all LUNs once we report
	 * it to that nexus once.  This bit is required as of SPC-4.
	 */
	eid_ptr->flags4 = SVPD_EID_LUICLR;

	/*
	 * We support revert to defaults (RTD) bit in MODE SELECT.
	 */
	eid_ptr->flags5 = SVPD_EID_RTD_SUP;

	/*
	 * XXX KDM in order to correctly answer this, we would need
	 * information from the SIM to determine how much sense data it
	 * can send.  So this would really be a path inquiry field, most
	 * likely.  This can be set to a maximum of 252 according to SPC-4,
	 * but the hardware may or may not be able to support that much.
	 * 0 just means that the maximum sense data length is not reported.
	 */
	eid_ptr->max_sense_length = 0;

	ctl_set_success(ctsio);
	ctsio->io_hdr.flags |= CTL_FLAG_ALLOCATED;
	ctsio->be_move_done = ctl_config_move_done;
	ctl_datamove((union ctl_io *)ctsio);
	return (CTL_RETVAL_COMPLETE);
}