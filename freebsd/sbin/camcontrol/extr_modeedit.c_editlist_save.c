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
typedef  int /*<<< orphan*/  u_int8_t ;
struct scsi_mode_page_header_sp {int page_length; } ;
struct scsi_mode_page_header {int page_code; size_t page_length; } ;
struct scsi_mode_header_6 {scalar_t__ blk_desc_len; int data_length; scalar_t__ dev_spec; } ;
struct scsi_mode_header_10 {scalar_t__ blk_desc_len; int data_length; scalar_t__ dev_spec; } ;
struct cam_device {scalar_t__ pd_type; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int MAX_DATA_SIZE ; 
 size_t MIN (size_t,int) ; 
 scalar_t__ PAGE_CTRL_SHIFT ; 
 int SMPH_PS ; 
 int SMPH_SPF ; 
 scalar_t__ SMS_PAGE_CTRL_SAVED ; 
 scalar_t__ T_SEQUENTIAL ; 
 int /*<<< orphan*/  bcopy (struct scsi_mode_page_header*,struct scsi_mode_header_6*,int) ; 
 int /*<<< orphan*/  buff_encode_visit (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  editentry_save ; 
 int /*<<< orphan*/  editlist_changed ; 
 struct scsi_mode_page_header* find_mode_page_10 (struct scsi_mode_header_6*) ; 
 struct scsi_mode_page_header* find_mode_page_6 (struct scsi_mode_header_6*) ; 
 int /*<<< orphan*/  format ; 
 int /*<<< orphan*/  mode_select (struct cam_device*,int,int,int,int,int,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  mode_sense (struct cam_device*,int*,int,int /*<<< orphan*/ ,int,int,int,int,int,int,int /*<<< orphan*/ *,int) ; 
 int scsi_2btoul (int) ; 
 int /*<<< orphan*/  scsi_ulto2b (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
editlist_save(struct cam_device *device, int cdb_len, int dbd, int pc,
    int page, int subpage, int task_attr, int retries, int timeout)
{
	u_int8_t data[MAX_DATA_SIZE];	/* Buffer to hold mode parameters. */
	u_int8_t *mode_pars;		/* Pointer to modepage params. */
	struct scsi_mode_page_header *mph;
	struct scsi_mode_page_header_sp *mphsp;
	size_t len, hlen, mphlen;

	/* Make sure that something changed before continuing. */
	if (! editlist_changed)
		return;

	/* Preload the CDB buffer with the current mode page data. */
	mode_sense(device, &cdb_len, dbd, 0, pc, page, subpage, task_attr,
	    retries, timeout, data, sizeof(data));

	/* Initial headers & offsets. */
	/*
	 * Tape drives include write protect (WP), Buffered Mode and Speed
	 * settings in the device-specific parameter.  Clearing this
	 * parameter on a mode select can have the effect of turning off
	 * write protect or buffered mode, or changing the speed setting of
	 * the tape drive.
	 *
	 * Disks report DPO/FUA support via the device specific parameter
	 * for MODE SENSE, but the bit is reserved for MODE SELECT.  So we
	 * clear this for disks (and other non-tape devices) to avoid
	 * potential errors from the target device.
	 */
	if (cdb_len == 6) {
		struct scsi_mode_header_6 *mh =
		    (struct scsi_mode_header_6 *)data;
		hlen = sizeof(*mh);
		/* Eliminate block descriptors. */
		if (mh->blk_desc_len > 0) {
			bcopy(find_mode_page_6(mh), mh + 1,
			    mh->data_length + 1 - hlen -
			    mh->blk_desc_len);
			mh->blk_desc_len = 0;
		}
		mh->data_length = 0;	/* Reserved for MODE SELECT command. */
		if (device->pd_type != T_SEQUENTIAL)
			mh->dev_spec = 0;	/* See comment above */
		mph = find_mode_page_6(mh);
	} else {
		struct scsi_mode_header_10 *mh =
		    (struct scsi_mode_header_10 *)data;
		hlen = sizeof(*mh);
		/* Eliminate block descriptors. */
		if (scsi_2btoul(mh->blk_desc_len) > 0) {
			bcopy(find_mode_page_10(mh), mh + 1,
			    scsi_2btoul(mh->data_length) + 1 - hlen -
			    scsi_2btoul(mh->blk_desc_len));
			scsi_ulto2b(0, mh->blk_desc_len);
		}
		scsi_ulto2b(0, mh->data_length); /* Reserved for MODE SELECT. */
		if (device->pd_type != T_SEQUENTIAL)
			mh->dev_spec = 0;	/* See comment above */
		mph = find_mode_page_10(mh);
	}
	if ((mph->page_code & SMPH_SPF) == 0) {
		mphlen = sizeof(*mph);
		mode_pars = (uint8_t *)(mph + 1);
		len = mph->page_length;
	} else {
		mphsp = (struct scsi_mode_page_header_sp *)mph;
		mphlen = sizeof(*mphsp);
		mode_pars = (uint8_t *)(mphsp + 1);
		len = scsi_2btoul(mphsp->page_length);
	}
	len = MIN(len, sizeof(data) - (mode_pars - data));

	/* Encode the value data to be passed back to the device. */
	buff_encode_visit(mode_pars, len, format, editentry_save, 0);

	mph->page_code &= ~SMPH_PS;	/* Reserved for MODE SELECT command. */

	/*
	 * Write the changes back to the device. If the user editted control
	 * page 3 (saved values) then request the changes be permanently
	 * recorded.
	 */
	mode_select(device, cdb_len, (pc << PAGE_CTRL_SHIFT == SMS_PAGE_CTRL_SAVED),
	    task_attr, retries, timeout, data, hlen + mphlen + len);
}