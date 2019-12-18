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
struct scsi_sense_sks {int* sense_key_spec; } ;
struct scsi_sense_desc_header {int dummy; } ;
struct scsi_sense_data {int dummy; } ;
struct scsi_inquiry_data {int dummy; } ;
struct sbuf {int dummy; } ;

/* Variables and functions */
 int SSD_SKS_VALID ; 
 int /*<<< orphan*/  scsi_extract_sense_len (struct scsi_sense_data*,int /*<<< orphan*/ ,int*,int*,int*,int*,int) ; 
 int /*<<< orphan*/  scsi_sks_sbuf (struct sbuf*,int,int*) ; 

void
scsi_sense_sks_sbuf(struct sbuf *sb, struct scsi_sense_data *sense,
		    u_int sense_len, uint8_t *cdb, int cdb_len,
		    struct scsi_inquiry_data *inq_data,
		    struct scsi_sense_desc_header *header)
{
	struct scsi_sense_sks *sks;
	int error_code, sense_key, asc, ascq;

	sks = (struct scsi_sense_sks *)header;

	if ((sks->sense_key_spec[0] & SSD_SKS_VALID) == 0)
		return;

	scsi_extract_sense_len(sense, sense_len, &error_code, &sense_key,
			       &asc, &ascq, /*show_errors*/ 1);

	scsi_sks_sbuf(sb, sense_key, sks->sense_key_spec);
}