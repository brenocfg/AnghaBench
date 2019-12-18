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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t u_int ;
struct scsi_sense_desc_printer {scalar_t__ desc_type; int /*<<< orphan*/  (* print_func ) (struct sbuf*,struct scsi_sense_data*,size_t,int /*<<< orphan*/ *,int,struct scsi_inquiry_data*,struct scsi_sense_desc_header*) ;} ;
struct scsi_sense_desc_header {scalar_t__ desc_type; } ;
struct scsi_sense_data {int dummy; } ;
struct scsi_inquiry_data {int dummy; } ;
struct sbuf {int dummy; } ;

/* Variables and functions */
 size_t nitems (struct scsi_sense_desc_printer*) ; 
 int /*<<< orphan*/  scsi_sense_generic_sbuf (struct sbuf*,struct scsi_sense_data*,size_t,int /*<<< orphan*/ *,int,struct scsi_inquiry_data*,struct scsi_sense_desc_header*) ; 
 struct scsi_sense_desc_printer* scsi_sense_printers ; 
 int /*<<< orphan*/  stub1 (struct sbuf*,struct scsi_sense_data*,size_t,int /*<<< orphan*/ *,int,struct scsi_inquiry_data*,struct scsi_sense_desc_header*) ; 

void
scsi_sense_desc_sbuf(struct sbuf *sb, struct scsi_sense_data *sense,
		     u_int sense_len, uint8_t *cdb, int cdb_len,
		     struct scsi_inquiry_data *inq_data,
		     struct scsi_sense_desc_header *header)
{
	u_int i;

	for (i = 0; i < nitems(scsi_sense_printers); i++) {
		struct scsi_sense_desc_printer *printer;

		printer = &scsi_sense_printers[i];

		/*
		 * The list is sorted, so quit if we've passed our
		 * descriptor number.
		 */
		if (printer->desc_type > header->desc_type)
			break;

		if (printer->desc_type != header->desc_type)
			continue;

		printer->print_func(sb, sense, sense_len, cdb, cdb_len,
				    inq_data, header);

		return;
	}

	/*
	 * No specific printing routine, so use the generic routine.
	 */
	scsi_sense_generic_sbuf(sb, sense, sense_len, cdb, cdb_len,
				inq_data, header);
}