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
struct ctl_scsiio {int dummy; } ;
typedef  int /*<<< orphan*/  str ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SSS_FLAG_PRINT_COMMAND ; 
 int /*<<< orphan*/  ctl_scsi_sense_sbuf (struct ctl_scsiio*,struct scsi_inquiry_data*,struct sbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 char* sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_new (struct sbuf*,char*,int,int /*<<< orphan*/ ) ; 

void
ctl_scsi_sense_print(struct ctl_scsiio *ctsio,
		     struct scsi_inquiry_data *inq_data, FILE *ofile)
{
	struct sbuf sb;
	char str[512];

	if ((ctsio == NULL) || (ofile == NULL))
		return;

	sbuf_new(&sb, str, sizeof(str), 0);

	ctl_scsi_sense_sbuf(ctsio, inq_data, &sb, SSS_FLAG_PRINT_COMMAND);

	sbuf_finish(&sb);

	fprintf(ofile, "%s", sbuf_data(&sb));
}