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
struct scsi_sense_desc_header {int length; int /*<<< orphan*/  desc_type; } ;
struct scsi_sense_data {int dummy; } ;
struct scsi_inquiry_data {int dummy; } ;
struct sbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int /*<<< orphan*/ ) ; 

void
scsi_sense_generic_sbuf(struct sbuf *sb, struct scsi_sense_data *sense,
			u_int sense_len, uint8_t *cdb, int cdb_len,
			struct scsi_inquiry_data *inq_data,
			struct scsi_sense_desc_header *header)
{
	int i;
	uint8_t *buf_ptr;

	sbuf_printf(sb, "Descriptor %#x:", header->desc_type);

	buf_ptr = (uint8_t *)&header[1];

	for (i = 0; i < header->length; i++, buf_ptr++)
		sbuf_printf(sb, " %02x", *buf_ptr);
}