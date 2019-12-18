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
 int /*<<< orphan*/  INSET ; 
 TYPE_1__* dev_select ; 
 int getmaxy (int /*<<< orphan*/ ) ; 
 int kbpt ; 
 int linesperregion ; 
 int /*<<< orphan*/  mvwaddstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mvwprintw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int num_devices ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wnd ; 

__attribute__((used)) static int
barlabels(int row)
{
	int i;
	char tmpstr[10];

	mvwaddstr(wnd, row++, INSET,
	    "/0%  /10  /20  /30  /40  /50  /60  /70  /80  /90  /100");
	linesperregion = 2 + kbpt;
	for (i = 0; i < num_devices; i++)
		if (dev_select[i].selected) {
			if (row > getmaxy(wnd) - 1 - linesperregion)
				break;
			sprintf(tmpstr, "%s%d", dev_select[i].device_name,
				dev_select[i].unit_number);
			mvwprintw(wnd, row++, 0, "%-5.5s MB/s|",
				  tmpstr);
			mvwaddstr(wnd, row++, 0, "      tps|");
			if (kbpt)
				mvwaddstr(wnd, row++, 0, "     KB/t|");
		}
	return (row);
}