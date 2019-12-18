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
struct scsi_inquiry_data {int dummy; } ;
struct sbuf {int dummy; } ;
struct ctl_scsiio {int /*<<< orphan*/ * cdb; } ;
typedef  int /*<<< orphan*/  cdb_str ;

/* Variables and functions */
 int SCSI_MAX_CDBLEN ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_cdb_string (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  scsi_op_desc (int /*<<< orphan*/ ,struct scsi_inquiry_data*) ; 

int
ctl_scsi_command_string(struct ctl_scsiio *ctsio,
			struct scsi_inquiry_data *inq_data, struct sbuf *sb)
{
	char cdb_str[(SCSI_MAX_CDBLEN * 3) + 1];

	sbuf_printf(sb, "%s. CDB: %s",
		    scsi_op_desc(ctsio->cdb[0], inq_data),
		    scsi_cdb_string(ctsio->cdb, cdb_str, sizeof(cdb_str)));

	return(0);
}