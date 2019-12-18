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
typedef  int /*<<< orphan*/  u_int ;
struct scsi_sense_desc_header {int desc_type; } ;
struct scsi_sense_data_desc {int dummy; } ;
struct scsi_sense_data {int dummy; } ;
struct scsi_print_sense_info {int /*<<< orphan*/  sb; int /*<<< orphan*/  inq_data; int /*<<< orphan*/  cdb_len; int /*<<< orphan*/  cdb; int /*<<< orphan*/  path_str; } ;

/* Variables and functions */
#define  SSD_DESC_BLOCK 133 
#define  SSD_DESC_COMMAND 132 
#define  SSD_DESC_FRU 131 
#define  SSD_DESC_INFO 130 
#define  SSD_DESC_SKS 129 
#define  SSD_DESC_STREAM 128 
 int /*<<< orphan*/  sbuf_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  scsi_sense_desc_sbuf (int /*<<< orphan*/ ,struct scsi_sense_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct scsi_sense_desc_header*) ; 

__attribute__((used)) static int
scsi_print_desc_func(struct scsi_sense_data_desc *sense, u_int sense_len,
		     struct scsi_sense_desc_header *header, void *arg)
{
	struct scsi_print_sense_info *print_info;

	print_info = (struct scsi_print_sense_info *)arg;

	switch (header->desc_type) {
	case SSD_DESC_INFO:
	case SSD_DESC_FRU:
	case SSD_DESC_COMMAND:
	case SSD_DESC_SKS:
	case SSD_DESC_BLOCK:
	case SSD_DESC_STREAM:
		/*
		 * We have already printed these descriptors, if they are
		 * present.
		 */
		break;
	default: {
		sbuf_printf(print_info->sb, "%s", print_info->path_str);
		scsi_sense_desc_sbuf(print_info->sb,
				     (struct scsi_sense_data *)sense, sense_len,
				     print_info->cdb, print_info->cdb_len,
				     print_info->inq_data, header);
		sbuf_printf(print_info->sb, "\n");
		break;
	}
	}

	/*
	 * Tell the iterator that we want to see more descriptors if they
	 * are present.
	 */
	return (0);
}