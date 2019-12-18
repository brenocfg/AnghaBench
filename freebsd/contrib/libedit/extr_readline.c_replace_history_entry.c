#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  histdata_t ;
struct TYPE_8__ {int /*<<< orphan*/ * line; int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int num; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ HistEvent ;
typedef  TYPE_2__ HIST_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  H_CURR ; 
 int /*<<< orphan*/  H_LAST ; 
 int /*<<< orphan*/  H_NEXT_EVDATA ; 
 int /*<<< orphan*/  H_REPLACE ; 
 int /*<<< orphan*/  H_SET ; 
 int /*<<< orphan*/ * e ; 
 int /*<<< orphan*/  el_free (TYPE_2__*) ; 
 TYPE_2__* el_malloc (int) ; 
 int /*<<< orphan*/ * h ; 
 scalar_t__ history (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  rl_initialize () ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ ) ; 

HIST_ENTRY *
replace_history_entry(int num, const char *line, histdata_t data)
{
	HIST_ENTRY *he;
	HistEvent ev;
	int curr_num;

	if (h == NULL || e == NULL)
		rl_initialize();

	/* save current position */
	if (history(h, &ev, H_CURR) != 0)
		return NULL;
	curr_num = ev.num;

	/* start from the oldest */
	if (history(h, &ev, H_LAST) != 0)
		return NULL;	/* error */

	if ((he = el_malloc(sizeof(*he))) == NULL)
		return NULL;

	/* look forwards for event matching specified offset */
	if (history(h, &ev, H_NEXT_EVDATA, num, &he->data))
		goto out;

	he->line = strdup(ev.str);
	if (he->line == NULL)
		goto out;

	if (history(h, &ev, H_REPLACE, line, data))
		goto out;

	/* restore pointer to where it was */
	if (history(h, &ev, H_SET, curr_num))
		goto out;

	return he;
out:
	el_free(he);
	return NULL;
}