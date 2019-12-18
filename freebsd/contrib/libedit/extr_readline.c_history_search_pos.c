#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int num; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ HistEvent ;

/* Variables and functions */
 int /*<<< orphan*/  H_CURR ; 
 int /*<<< orphan*/  H_NEXT ; 
 int /*<<< orphan*/  H_NEXT_EVENT ; 
 int /*<<< orphan*/  H_PREV ; 
 int /*<<< orphan*/  H_PREV_EVENT ; 
 int /*<<< orphan*/  h ; 
 int /*<<< orphan*/  history (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  history_set_pos (int) ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char const*) ; 

int
history_search_pos(const char *str,
		   int direction __attribute__((__unused__)), int pos)
{
	HistEvent ev;
	int curr_num, off;

	off = (pos > 0) ? pos : -pos;
	pos = (pos > 0) ? 1 : -1;

	if (history(h, &ev, H_CURR) != 0)
		return -1;
	curr_num = ev.num;

	if (!history_set_pos(off) || history(h, &ev, H_CURR) != 0)
		return -1;

	for (;;) {
		if (strstr(ev.str, str))
			return off;
		if (history(h, &ev, (pos < 0) ? H_PREV : H_NEXT) != 0)
			break;
	}

	/* set "current" pointer back to previous state */
	(void)history(h, &ev,
	    pos < 0 ? H_NEXT_EVENT : H_PREV_EVENT, curr_num);

	return -1;
}