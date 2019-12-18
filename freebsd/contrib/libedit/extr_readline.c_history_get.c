#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  line; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int num; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ HistEvent ;
typedef  TYPE_2__ HIST_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  H_CURR ; 
 int /*<<< orphan*/  H_DELDATA ; 
 int /*<<< orphan*/  H_NEXT_EVDATA ; 
 int /*<<< orphan*/  H_SET ; 
 int /*<<< orphan*/ * e ; 
 int /*<<< orphan*/ * h ; 
 scalar_t__ history (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,...) ; 
 int history_base ; 
 int /*<<< orphan*/  rl_initialize () ; 

HIST_ENTRY *
history_get(int num)
{
	static HIST_ENTRY she;
	HistEvent ev;
	int curr_num;

	if (h == NULL || e == NULL)
		rl_initialize();

	if (num < history_base)
		return NULL;

	/* save current position */
	if (history(h, &ev, H_CURR) != 0)
		return NULL;
	curr_num = ev.num;

	/*
	 * use H_DELDATA to set to nth history (without delete) by passing
	 * (void **)-1  -- as in history_set_pos
	 */
	if (history(h, &ev, H_DELDATA, num - history_base, (void **)-1) != 0)
		goto out;

	/* get current entry */
	if (history(h, &ev, H_CURR) != 0)
		goto out;
	if (history(h, &ev, H_NEXT_EVDATA, ev.num, &she.data) != 0)
		goto out;
	she.line = ev.str;

	/* restore pointer to where it was */
	(void)history(h, &ev, H_SET, curr_num);

	return &she;

out:
	/* restore pointer to where it was */
	(void)history(h, &ev, H_SET, curr_num);
	return NULL;
}