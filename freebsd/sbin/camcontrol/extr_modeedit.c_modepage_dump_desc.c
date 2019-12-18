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
typedef  int uint8_t ;
struct scsi_mode_header_6 {size_t blk_desc_len; } ;
struct scsi_mode_header_10 {int /*<<< orphan*/  blk_desc_len; } ;
struct cam_device {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int MAX_DATA_SIZE ; 
 size_t MIN (size_t,int) ; 
 int /*<<< orphan*/  mode_sense (struct cam_device*,int*,int /*<<< orphan*/ ,int,int,int,int,int,int,int,int*,int) ; 
 int /*<<< orphan*/  printf (char*,int,char) ; 
 int /*<<< orphan*/  putchar (char) ; 
 size_t scsi_2btoul (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
modepage_dump_desc(struct cam_device *device, int cdb_len, int llbaa, int pc,
	      int page, int subpage, int task_attr, int retries, int timeout)
{
	uint8_t data[MAX_DATA_SIZE];	/* Buffer to hold mode parameters. */
	uint8_t *desc;			/* Pointer to block descriptor. */
	size_t indx, len;

	mode_sense(device, &cdb_len, 0, llbaa, pc, page, subpage, task_attr,
	    retries, timeout, data, sizeof(data));

	if (cdb_len == 6) {
		struct scsi_mode_header_6 *mh =
		    (struct scsi_mode_header_6 *)data;
		desc = (uint8_t *)(mh + 1);
		len = mh->blk_desc_len;
	} else {
		struct scsi_mode_header_10 *mh =
		    (struct scsi_mode_header_10 *)data;
		desc = (uint8_t *)(mh + 1);
		len = scsi_2btoul(mh->blk_desc_len);
	}
	len = MIN(len, sizeof(data) - (desc - data));

	/* Print the raw mode page data with newlines each 8 bytes. */
	for (indx = 0; indx < len; indx++) {
		printf("%02x%c", desc[indx],
		    (((indx + 1) % 8) == 0) ? '\n' : ' ');
	}
	putchar('\n');
}