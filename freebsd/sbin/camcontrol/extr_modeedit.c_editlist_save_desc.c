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
struct scsi_mode_header_6 {size_t blk_desc_len; scalar_t__ dev_spec; scalar_t__ data_length; } ;
struct scsi_mode_header_10 {scalar_t__ dev_spec; int /*<<< orphan*/  data_length; int /*<<< orphan*/  blk_desc_len; } ;
struct cam_device {scalar_t__ pd_type; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int MAX_DATA_SIZE ; 
 size_t MIN (size_t,int) ; 
 scalar_t__ PAGE_CTRL_SHIFT ; 
 scalar_t__ SMS_PAGE_CTRL_SAVED ; 
 scalar_t__ T_SEQUENTIAL ; 
 int /*<<< orphan*/  buff_encode_visit (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  editentry_save ; 
 int /*<<< orphan*/  editlist_changed ; 
 int /*<<< orphan*/  format ; 
 int /*<<< orphan*/  mode_select (struct cam_device*,int,int,int,int,int,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  mode_sense (struct cam_device*,int*,int /*<<< orphan*/ ,int,int,int,int,int,int,int,int /*<<< orphan*/ *,int) ; 
 size_t scsi_2btoul (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto2b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
editlist_save_desc(struct cam_device *device, int cdb_len, int llbaa, int pc,
    int page, int subpage, int task_attr, int retries, int timeout)
{
	uint8_t data[MAX_DATA_SIZE];	/* Buffer to hold mode parameters. */
	uint8_t *desc;			/* Pointer to block descriptor. */
	size_t len, hlen;

	/* Make sure that something changed before continuing. */
	if (! editlist_changed)
		return;

	/* Preload the CDB buffer with the current mode page data. */
	mode_sense(device, &cdb_len, 0, llbaa, pc, page, subpage, task_attr,
	    retries, timeout, data, sizeof(data));

	/* Initial headers & offsets. */
	if (cdb_len == 6) {
		struct scsi_mode_header_6 *mh =
		    (struct scsi_mode_header_6 *)data;
		hlen = sizeof(*mh);
		desc = (uint8_t *)(mh + 1);
		len = mh->blk_desc_len;
		mh->data_length = 0;	/* Reserved for MODE SELECT command. */
		if (device->pd_type != T_SEQUENTIAL)
			mh->dev_spec = 0;	/* See comment above */
	} else {
		struct scsi_mode_header_10 *mh =
		    (struct scsi_mode_header_10 *)data;
		hlen = sizeof(*mh);
		desc = (uint8_t *)(mh + 1);
		len = scsi_2btoul(mh->blk_desc_len);
		scsi_ulto2b(0, mh->data_length); /* Reserved for MODE SELECT. */
		if (device->pd_type != T_SEQUENTIAL)
			mh->dev_spec = 0;	/* See comment above */
	}
	len = MIN(len, sizeof(data) - (desc - data));

	/* Encode the value data to be passed back to the device. */
	buff_encode_visit(desc, len, format, editentry_save, 0);

	/*
	 * Write the changes back to the device. If the user editted control
	 * page 3 (saved values) then request the changes be permanently
	 * recorded.
	 */
	mode_select(device, cdb_len, (pc << PAGE_CTRL_SHIFT == SMS_PAGE_CTRL_SAVED),
	    task_attr, retries, timeout, data, hlen + len);
}