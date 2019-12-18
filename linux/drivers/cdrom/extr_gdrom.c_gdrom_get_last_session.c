#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lba; } ;
struct cdrom_multisession {int xa_flag; TYPE_1__ addr; int /*<<< orphan*/  addr_format; } ;
struct cdrom_device_info {int dummy; } ;
struct TYPE_6__ {TYPE_2__* toc; } ;
struct TYPE_5__ {int* entry; int /*<<< orphan*/  first; int /*<<< orphan*/  last; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDROM_LBA ; 
 int ENOMEM ; 
 int ENXIO ; 
 TYPE_3__ gd ; 
 int /*<<< orphan*/  gdrom_getsense (int /*<<< orphan*/ *) ; 
 int gdrom_readtoc_cmd (TYPE_2__*,int) ; 
 int /*<<< orphan*/  get_entry_lba (int) ; 
 scalar_t__ get_entry_q_ctrl (int) ; 
 int get_entry_track (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static int gdrom_get_last_session(struct cdrom_device_info *cd_info,
	struct cdrom_multisession *ms_info)
{
	int fentry, lentry, track, data, err;

	if (!gd.toc)
		return -ENOMEM;

	/* Check if GD-ROM */
	err = gdrom_readtoc_cmd(gd.toc, 1);
	/* Not a GD-ROM so check if standard CD-ROM */
	if (err) {
		err = gdrom_readtoc_cmd(gd.toc, 0);
		if (err) {
			pr_info("Could not get CD table of contents\n");
			return -ENXIO;
		}
	}

	fentry = get_entry_track(gd.toc->first);
	lentry = get_entry_track(gd.toc->last);
	/* Find the first data track */
	track = get_entry_track(gd.toc->last);
	do {
		data = gd.toc->entry[track - 1];
		if (get_entry_q_ctrl(data))
			break;	/* ie a real data track */
		track--;
	} while (track >= fentry);

	if ((track > 100) || (track < get_entry_track(gd.toc->first))) {
		pr_info("No data on the last session of the CD\n");
		gdrom_getsense(NULL);
		return -ENXIO;
	}

	ms_info->addr_format = CDROM_LBA;
	ms_info->addr.lba = get_entry_lba(data);
	ms_info->xa_flag = 1;
	return 0;
}