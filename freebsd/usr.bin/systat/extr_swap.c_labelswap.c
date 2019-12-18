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
struct TYPE_2__ {char* ksw_devname; } ;

/* Variables and functions */
 int /*<<< orphan*/  dlen ; 
 int /*<<< orphan*/  dslabel (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fetchswap () ; 
 int /*<<< orphan*/  header ; 
 int /*<<< orphan*/  hlen ; 
 TYPE_1__* kvmsw ; 
 int kvnsw ; 
 int /*<<< orphan*/  mvwprintw (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  ulen ; 
 int /*<<< orphan*/  werase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wnd ; 

void
labelswap(void)
{
	const char *name;
	int i;

	fetchswap();

	werase(wnd);

	mvwprintw(wnd, 0, 0, "%*s%*s%*s %s",
	    -dlen, "Disk", hlen, header, ulen, "Used",
	    "/0%  /10  /20  /30  /40  /50  /60  /70  /80  /90  /100");

	for (i = 0; i <= kvnsw; ++i) {
		if (i == kvnsw) {
			if (kvnsw == 1)
				break;
			name = "Total";
		} else
			name = kvmsw[i].ksw_devname;
		mvwprintw(wnd, i + 1, 0, "%*s", -dlen, name);
	}
	dslabel(12, 0, 18);
}