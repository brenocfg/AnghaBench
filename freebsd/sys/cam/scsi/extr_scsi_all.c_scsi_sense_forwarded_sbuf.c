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
typedef  int /*<<< orphan*/  u_int ;
struct scsi_sense_forwarded {scalar_t__ length; scalar_t__ sense_data; } ;
struct scsi_sense_desc_header {int dummy; } ;
struct scsi_sense_data {int dummy; } ;
struct scsi_inquiry_data {int dummy; } ;
struct sbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,char const*,int,int,char const*) ; 
 int /*<<< orphan*/  scsi_extract_sense_len (struct scsi_sense_data*,scalar_t__,int*,int*,int*,int*,int) ; 
 int /*<<< orphan*/  scsi_sense_desc (int,int,int,int /*<<< orphan*/ *,char const**,char const**) ; 

void
scsi_sense_forwarded_sbuf(struct sbuf *sb, struct scsi_sense_data *sense,
			 u_int sense_len, uint8_t *cdb, int cdb_len,
			 struct scsi_inquiry_data *inq_data,
			 struct scsi_sense_desc_header *header)
{
	struct scsi_sense_forwarded *forwarded;
	const char *sense_key_desc;
	const char *asc_desc;
	int error_code, sense_key, asc, ascq;

	forwarded = (struct scsi_sense_forwarded *)header;
	scsi_extract_sense_len((struct scsi_sense_data *)forwarded->sense_data,
	    forwarded->length - 2, &error_code, &sense_key, &asc, &ascq, 1);
	scsi_sense_desc(sense_key, asc, ascq, NULL, &sense_key_desc, &asc_desc);

	sbuf_printf(sb, "Forwarded sense: %s asc:%x,%x (%s): ",
	    sense_key_desc, asc, ascq, asc_desc);
}