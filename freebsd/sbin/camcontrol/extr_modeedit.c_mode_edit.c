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
struct cam_device {int dummy; } ;

/* Variables and functions */
 char* DEFAULT_SCSI_MODE_DB ; 
 scalar_t__ ENOENT ; 
 scalar_t__ ESRCH ; 
 int /*<<< orphan*/  EX_OSFILE ; 
 int /*<<< orphan*/  EX_USAGE ; 
 scalar_t__ PAGE_CTRL_SHIFT ; 
 scalar_t__ SMS_PAGE_CTRL_CURRENT ; 
 scalar_t__ SMS_PAGE_CTRL_SAVED ; 
 scalar_t__ STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  editlist ; 
 int /*<<< orphan*/  editlist_populate (struct cam_device*,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  editlist_populate_desc (struct cam_device*,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  editlist_save (struct cam_device*,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  editlist_save_desc (struct cam_device*,int,int,int,int,int,int,int,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 scalar_t__ load_format (char const*,int,int) ; 
 int /*<<< orphan*/  modepage_dump (struct cam_device*,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  modepage_dump_desc (struct cam_device*,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  modepage_edit () ; 
 int /*<<< orphan*/  modepage_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

void
mode_edit(struct cam_device *device, int cdb_len, int desc, int dbd, int llbaa,
    int pc, int page, int subpage, int edit, int binary, int task_attr,
    int retry_count, int timeout)
{
	const char *pagedb_path;	/* Path to modepage database. */

	if (binary) {
		if (edit)
			errx(EX_USAGE, "cannot edit in binary mode.");
	} else if (desc) {
		editlist_populate_desc(device, cdb_len, llbaa, pc, page,
		    subpage, task_attr, retry_count, timeout);
	} else {
		if ((pagedb_path = getenv("SCSI_MODES")) == NULL)
			pagedb_path = DEFAULT_SCSI_MODE_DB;

		if (load_format(pagedb_path, page, subpage) != 0 &&
		    (edit || verbose)) {
			if (errno == ENOENT) {
				/* Modepage database file not found. */
				warn("cannot open modepage database \"%s\"",
				    pagedb_path);
			} else if (errno == ESRCH) {
				/* Modepage entry not found in database. */
				warnx("modepage 0x%02x,0x%02x not found in "
				    "database \"%s\"", page, subpage,
				    pagedb_path);
			}
			/* We can recover in display mode, otherwise we exit. */
			if (!edit) {
				warnx("reverting to binary display only");
				binary = 1;
			} else
				exit(EX_OSFILE);
		}

		editlist_populate(device, cdb_len, dbd, pc, page, subpage,
		    task_attr, retry_count, timeout);
	}

	if (edit) {
		if (pc << PAGE_CTRL_SHIFT != SMS_PAGE_CTRL_CURRENT &&
		    pc << PAGE_CTRL_SHIFT != SMS_PAGE_CTRL_SAVED)
			errx(EX_USAGE, "it only makes sense to edit page 0 "
			    "(current) or page 3 (saved values)");
		modepage_edit();
		if (desc) {
			editlist_save_desc(device, cdb_len, llbaa, pc, page,
			    subpage, task_attr, retry_count, timeout);
		} else {
			editlist_save(device, cdb_len, dbd, pc, page, subpage,
			    task_attr, retry_count, timeout);
		}
	} else if (binary || STAILQ_EMPTY(&editlist)) {
		/* Display without formatting information. */
		if (desc) {
			modepage_dump_desc(device, cdb_len, llbaa, pc, page,
			    subpage, task_attr, retry_count, timeout);
		} else {
			modepage_dump(device, cdb_len, dbd, pc, page, subpage,
			    task_attr, retry_count, timeout);
		}
	} else {
		/* Display with format. */
		modepage_write(stdout, 0);
	}
}