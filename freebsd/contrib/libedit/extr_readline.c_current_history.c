#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  line; } ;
struct TYPE_6__ {int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ HistEvent ;
typedef  TYPE_2__ HIST_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  H_PREV_EVENT ; 
 int /*<<< orphan*/  h ; 
 scalar_t__ history (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ history_offset ; 
 TYPE_2__ rl_he ; 

HIST_ENTRY *
current_history(void)
{
	HistEvent ev;

	if (history(h, &ev, H_PREV_EVENT, history_offset + 1) != 0)
		return NULL;

	rl_he.line = ev.str;
	rl_he.data = NULL;
	return &rl_he;
}