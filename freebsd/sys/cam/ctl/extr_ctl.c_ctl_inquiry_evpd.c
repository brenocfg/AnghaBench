#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  union ctl_io {int dummy; } ctl_io ;
struct scsi_inquiry {int page_code; int /*<<< orphan*/  length; } ;
struct ctl_scsiio {scalar_t__ cdb; } ;
struct ctl_lun {TYPE_1__* be_lun; } ;
struct TYPE_2__ {int /*<<< orphan*/  lun_type; } ;

/* Variables and functions */
 struct ctl_lun* CTL_LUN (struct ctl_scsiio*) ; 
 int CTL_RETVAL_COMPLETE ; 
#define  SVPD_BDC 138 
#define  SVPD_BLOCK_LIMITS 137 
#define  SVPD_DEVICE_ID 136 
#define  SVPD_EXTENDED_INQUIRY_DATA 135 
#define  SVPD_LBP 134 
#define  SVPD_MODE_PAGE_POLICY 133 
#define  SVPD_SCSI_PORTS 132 
#define  SVPD_SCSI_SFS 131 
#define  SVPD_SCSI_TPC 130 
#define  SVPD_SUPPORTED_PAGES 129 
#define  SVPD_UNIT_SERIAL_NUMBER 128 
 int /*<<< orphan*/  T_DIRECT ; 
 int /*<<< orphan*/  ctl_done (union ctl_io*) ; 
 int ctl_inquiry_evpd_bdc (struct ctl_scsiio*,int) ; 
 int ctl_inquiry_evpd_block_limits (struct ctl_scsiio*,int) ; 
 int ctl_inquiry_evpd_devid (struct ctl_scsiio*,int) ; 
 int ctl_inquiry_evpd_eid (struct ctl_scsiio*,int) ; 
 int ctl_inquiry_evpd_lbp (struct ctl_scsiio*,int) ; 
 int ctl_inquiry_evpd_mpp (struct ctl_scsiio*,int) ; 
 int ctl_inquiry_evpd_scsi_ports (struct ctl_scsiio*,int) ; 
 int ctl_inquiry_evpd_serial (struct ctl_scsiio*,int) ; 
 int ctl_inquiry_evpd_sfs (struct ctl_scsiio*,int) ; 
 int ctl_inquiry_evpd_supported (struct ctl_scsiio*,int) ; 
 int ctl_inquiry_evpd_tpc (struct ctl_scsiio*,int) ; 
 int /*<<< orphan*/  ctl_set_invalid_field (struct ctl_scsiio*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int scsi_2btoul (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ctl_inquiry_evpd(struct ctl_scsiio *ctsio)
{
	struct ctl_lun *lun = CTL_LUN(ctsio);
	struct scsi_inquiry *cdb;
	int alloc_len, retval;

	cdb = (struct scsi_inquiry *)ctsio->cdb;
	alloc_len = scsi_2btoul(cdb->length);

	switch (cdb->page_code) {
	case SVPD_SUPPORTED_PAGES:
		retval = ctl_inquiry_evpd_supported(ctsio, alloc_len);
		break;
	case SVPD_UNIT_SERIAL_NUMBER:
		retval = ctl_inquiry_evpd_serial(ctsio, alloc_len);
		break;
	case SVPD_DEVICE_ID:
		retval = ctl_inquiry_evpd_devid(ctsio, alloc_len);
		break;
	case SVPD_EXTENDED_INQUIRY_DATA:
		retval = ctl_inquiry_evpd_eid(ctsio, alloc_len);
		break;
	case SVPD_MODE_PAGE_POLICY:
		retval = ctl_inquiry_evpd_mpp(ctsio, alloc_len);
		break;
	case SVPD_SCSI_PORTS:
		retval = ctl_inquiry_evpd_scsi_ports(ctsio, alloc_len);
		break;
	case SVPD_SCSI_TPC:
		retval = ctl_inquiry_evpd_tpc(ctsio, alloc_len);
		break;
	case SVPD_SCSI_SFS:
		retval = ctl_inquiry_evpd_sfs(ctsio, alloc_len);
		break;
	case SVPD_BLOCK_LIMITS:
		if (lun == NULL || lun->be_lun->lun_type != T_DIRECT)
			goto err;
		retval = ctl_inquiry_evpd_block_limits(ctsio, alloc_len);
		break;
	case SVPD_BDC:
		if (lun == NULL || lun->be_lun->lun_type != T_DIRECT)
			goto err;
		retval = ctl_inquiry_evpd_bdc(ctsio, alloc_len);
		break;
	case SVPD_LBP:
		if (lun == NULL || lun->be_lun->lun_type != T_DIRECT)
			goto err;
		retval = ctl_inquiry_evpd_lbp(ctsio, alloc_len);
		break;
	default:
err:
		ctl_set_invalid_field(ctsio,
				      /*sks_valid*/ 1,
				      /*command*/ 1,
				      /*field*/ 2,
				      /*bit_valid*/ 0,
				      /*bit*/ 0);
		ctl_done((union ctl_io *)ctsio);
		retval = CTL_RETVAL_COMPLETE;
		break;
	}

	return (retval);
}