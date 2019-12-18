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
struct TYPE_2__ {scalar_t__ config; } ;
struct ccb_getdev {int protocol; TYPE_1__ ident_data; } ;
struct cam_device {int dummy; } ;
typedef  int /*<<< orphan*/  camcontrol_devtype ;

/* Variables and functions */
 int /*<<< orphan*/  CC_DT_ATA ; 
 int /*<<< orphan*/  CC_DT_MMCSD ; 
 int /*<<< orphan*/  CC_DT_NVME ; 
 int /*<<< orphan*/  CC_DT_SATL ; 
 int /*<<< orphan*/  CC_DT_SCSI ; 
 int /*<<< orphan*/  CC_DT_UNKNOWN ; 
#define  PROTO_ATA 133 
#define  PROTO_ATAPI 132 
#define  PROTO_MMCSD 131 
#define  PROTO_NVME 130 
#define  PROTO_SATAPM 129 
#define  PROTO_SCSI 128 
 int /*<<< orphan*/  SVPD_ATA_INFORMATION ; 
 int dev_has_vpd_page (struct cam_device*,int /*<<< orphan*/ ,int,int,int) ; 
 int get_cgd (struct cam_device*,struct ccb_getdev*) ; 

int
get_device_type(struct cam_device *dev, int retry_count, int timeout,
		    int verbosemode, camcontrol_devtype *devtype)
{
	struct ccb_getdev cgd;
	int retval;

	retval = get_cgd(dev, &cgd);
	if (retval != 0)
		goto bailout;

	switch (cgd.protocol) {
	case PROTO_SCSI:
		break;
	case PROTO_ATA:
	case PROTO_ATAPI:
	case PROTO_SATAPM:
		*devtype = CC_DT_ATA;
		goto bailout;
		break; /*NOTREACHED*/
	case PROTO_NVME:
		*devtype = CC_DT_NVME;
		goto bailout;
		break; /*NOTREACHED*/
	case PROTO_MMCSD:
		*devtype = CC_DT_MMCSD;
		goto bailout;
		break; /*NOTREACHED*/
	default:
		*devtype = CC_DT_UNKNOWN;
		goto bailout;
		break; /*NOTREACHED*/
	}

	if (retry_count == -1) {
		/*
		 * For a retry count of -1, used only the cached data to avoid
		 * I/O to the drive. Sending the identify command to the drive
		 * can cause issues for SATL attachaed drives since identify is
		 * not an NCQ command.
		 */
		if (cgd.ident_data.config != 0)
			*devtype = CC_DT_SATL;
		else
			*devtype = CC_DT_SCSI;
	} else {
		/*
		 * Check for the ATA Information VPD page (0x89).  If this is an
		 * ATA device behind a SCSI to ATA translation layer (SATL),
		 * this VPD page should be present.
		 *
		 * If that VPD page isn't present, or we get an error back from
		 * the INQUIRY command, we'll just treat it as a normal SCSI
		 * device.
		 */
		retval = dev_has_vpd_page(dev, SVPD_ATA_INFORMATION, retry_count,
		    timeout, verbosemode);
		if (retval == 1)
			*devtype = CC_DT_SATL;
		else
			*devtype = CC_DT_SCSI;
	}
	retval = 0;

bailout:
	return (retval);
}