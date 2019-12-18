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
struct scsi_sense_desc_header {int dummy; } ;
struct scsi_sense_data {int dummy; } ;
struct scsi_sense_block {int /*<<< orphan*/  byte3; } ;
struct scsi_inquiry_data {int dummy; } ;
struct sbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_block_sbuf (struct sbuf*,int /*<<< orphan*/ ) ; 

void
scsi_sense_block_sbuf(struct sbuf *sb, struct scsi_sense_data *sense,
		      u_int sense_len, uint8_t *cdb, int cdb_len,
		      struct scsi_inquiry_data *inq_data,
		      struct scsi_sense_desc_header *header)
{
	struct scsi_sense_block *block;

	block = (struct scsi_sense_block *)header;
	scsi_block_sbuf(sb, block->byte3);
}