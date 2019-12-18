#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u_int8_t ;
struct scsi_inquiry_data {int dummy; } ;
struct sbuf {int dummy; } ;

/* Variables and functions */
 char* SCSI_REV_0 ; 
 char* SCSI_REV_SPC ; 
 char* SID_ANSI_REV (struct scsi_inquiry_data*) ; 
 scalar_t__ SID_IS_REMOVABLE (struct scsi_inquiry_data*) ; 
 int SID_QUAL (struct scsi_inquiry_data*) ; 
#define  SID_QUAL_BAD_LU 149 
 scalar_t__ SID_QUAL_IS_VENDOR_UNIQUE (struct scsi_inquiry_data*) ; 
#define  SID_QUAL_LU_CONNECTED 148 
#define  SID_QUAL_LU_OFFLINE 147 
#define  SID_QUAL_RSVD 146 
 int SID_TYPE (struct scsi_inquiry_data*) ; 
#define  T_ADC 145 
#define  T_CDROM 144 
#define  T_CHANGER 143 
#define  T_COMM 142 
#define  T_DIRECT 141 
#define  T_ENCLOSURE 140 
#define  T_NODEVICE 139 
#define  T_OCRW 138 
#define  T_OPTICAL 137 
#define  T_OSD 136 
#define  T_PRINTER 135 
#define  T_PROCESSOR 134 
#define  T_RBC 133 
#define  T_SCANNER 132 
#define  T_SEQUENTIAL 131 
#define  T_STORARRAY 130 
#define  T_WORM 129 
#define  T_ZBC_HM 128 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,...) ; 
 int /*<<< orphan*/  scsi_print_inquiry_short_sbuf (struct sbuf*,struct scsi_inquiry_data*) ; 

void
scsi_print_inquiry_sbuf(struct sbuf *sb, struct scsi_inquiry_data *inq_data)
{
	u_int8_t type;
	char *dtype, *qtype;

	type = SID_TYPE(inq_data);

	/*
	 * Figure out basic device type and qualifier.
	 */
	if (SID_QUAL_IS_VENDOR_UNIQUE(inq_data)) {
		qtype = " (vendor-unique qualifier)";
	} else {
		switch (SID_QUAL(inq_data)) {
		case SID_QUAL_LU_CONNECTED:
			qtype = "";
			break;

		case SID_QUAL_LU_OFFLINE:
			qtype = " (offline)";
			break;

		case SID_QUAL_RSVD:
			qtype = " (reserved qualifier)";
			break;
		default:
		case SID_QUAL_BAD_LU:
			qtype = " (LUN not supported)";
			break;
		}
	}

	switch (type) {
	case T_DIRECT:
		dtype = "Direct Access";
		break;
	case T_SEQUENTIAL:
		dtype = "Sequential Access";
		break;
	case T_PRINTER:
		dtype = "Printer";
		break;
	case T_PROCESSOR:
		dtype = "Processor";
		break;
	case T_WORM:
		dtype = "WORM";
		break;
	case T_CDROM:
		dtype = "CD-ROM";
		break;
	case T_SCANNER:
		dtype = "Scanner";
		break;
	case T_OPTICAL:
		dtype = "Optical";
		break;
	case T_CHANGER:
		dtype = "Changer";
		break;
	case T_COMM:
		dtype = "Communication";
		break;
	case T_STORARRAY:
		dtype = "Storage Array";
		break;
	case T_ENCLOSURE:
		dtype = "Enclosure Services";
		break;
	case T_RBC:
		dtype = "Simplified Direct Access";
		break;
	case T_OCRW:
		dtype = "Optical Card Read/Write";
		break;
	case T_OSD:
		dtype = "Object-Based Storage";
		break;
	case T_ADC:
		dtype = "Automation/Drive Interface";
		break;
	case T_ZBC_HM:
		dtype = "Host Managed Zoned Block";
		break;
	case T_NODEVICE:
		dtype = "Uninstalled";
		break;
	default:
		dtype = "unknown";
		break;
	}

	scsi_print_inquiry_short_sbuf(sb, inq_data);

	sbuf_printf(sb, "%s %s ", SID_IS_REMOVABLE(inq_data) ? "Removable" : "Fixed", dtype);

	if (SID_ANSI_REV(inq_data) == SCSI_REV_0)
		sbuf_printf(sb, "SCSI ");
	else if (SID_ANSI_REV(inq_data) <= SCSI_REV_SPC) {
		sbuf_printf(sb, "SCSI-%d ", SID_ANSI_REV(inq_data));
	} else {
		sbuf_printf(sb, "SPC-%d SCSI ", SID_ANSI_REV(inq_data) - 2);
	}
	sbuf_printf(sb, "device%s\n", qtype);
}