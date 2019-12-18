#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* device_name; int /*<<< orphan*/  unit_number; scalar_t__ selected; } ;

/* Variables and functions */
 TYPE_1__* dev_select ; 
 int /*<<< orphan*/  mvprintw (int,int,char*,...) ; 
 int num_devices ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int /*<<< orphan*/ ) ; 

void
dslabel(int maxdrives, int diskcol, int diskrow)
{
	int i, j;

	mvprintw(diskrow, diskcol, "Disks");
	mvprintw(diskrow + 1, diskcol, "KB/t");
	mvprintw(diskrow + 2, diskcol, "tps");
	mvprintw(diskrow + 3, diskcol, "MB/s");
	mvprintw(diskrow + 4, diskcol, "%%busy");
	/*
	 * For now, we don't support a fourth disk statistic.  So there's
	 * no point in providing a label for it.  If someone can think of a
	 * fourth useful disk statistic, there is room to add it.
	 */
	/* mvprintw(diskrow + 4, diskcol, " msps"); */
	j = 0;
	for (i = 0; i < num_devices && j < maxdrives; i++)
		if (dev_select[i].selected) {
			char tmpstr[80];
			sprintf(tmpstr, "%s%d", dev_select[i].device_name,
				dev_select[i].unit_number);
			mvprintw(diskrow, diskcol + 5 + 6 * j,
				" %5.5s", tmpstr);
			j++;
		}
}