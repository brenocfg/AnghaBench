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
typedef  int /*<<< orphan*/  vendor ;
struct scsi_inquiry_data {int /*<<< orphan*/  revision; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; } ;
struct mpt_standalone_disk {int /*<<< orphan*/  inqstring; } ;
typedef  int /*<<< orphan*/  rstr ;
typedef  int /*<<< orphan*/  revision ;
typedef  int /*<<< orphan*/  product ;

/* Variables and functions */
#define  SCSI_REV_CCS 128 
 int SID_ANSI_REV (struct scsi_inquiry_data*) ; 
 scalar_t__ SID_QUAL (struct scsi_inquiry_data*) ; 
 scalar_t__ SID_QUAL_IS_VENDOR_UNIQUE (struct scsi_inquiry_data*) ; 
 scalar_t__ SID_QUAL_LU_CONNECTED ; 
 scalar_t__ SID_TYPE (struct scsi_inquiry_data*) ; 
 scalar_t__ T_DIRECT ; 
 int /*<<< orphan*/  cam_strvis (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void
format_scsi_inquiry(struct mpt_standalone_disk *disk,
    struct scsi_inquiry_data *inq_data)
{
	char vendor[16], product[48], revision[16], rstr[12];

	if (SID_QUAL_IS_VENDOR_UNIQUE(inq_data))
		return;
	if (SID_TYPE(inq_data) != T_DIRECT)
		return;
	if (SID_QUAL(inq_data) != SID_QUAL_LU_CONNECTED)
		return;

	cam_strvis(vendor, inq_data->vendor, sizeof(inq_data->vendor),
	    sizeof(vendor));
	cam_strvis(product, inq_data->product, sizeof(inq_data->product),
	    sizeof(product));
	cam_strvis(revision, inq_data->revision, sizeof(inq_data->revision),
	    sizeof(revision));

	/* Hack for SATA disks, no idea how to tell speed. */
	if (strcmp(vendor, "ATA") == 0) {
		snprintf(disk->inqstring, sizeof(disk->inqstring),
		    "<%s %s> SATA", product, revision);
		return;
	}

	switch (SID_ANSI_REV(inq_data)) {
	case SCSI_REV_CCS:
		strcpy(rstr, "SCSI-CCS");
		break;
	case 5:
		strcpy(rstr, "SAS");
		break;
	default:
		snprintf(rstr, sizeof (rstr), "SCSI-%d",
		    SID_ANSI_REV(inq_data));
		break;
	}
	snprintf(disk->inqstring, sizeof(disk->inqstring), "<%s %s %s> %s",
	    vendor, product, revision, rstr);
}