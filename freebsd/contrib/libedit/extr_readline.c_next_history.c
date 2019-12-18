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
typedef  int /*<<< orphan*/  HistEvent ;
typedef  int /*<<< orphan*/  HIST_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  H_LAST ; 
 int /*<<< orphan*/ * current_history () ; 
 int /*<<< orphan*/  h ; 
 scalar_t__ history (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ history_length ; 
 scalar_t__ history_offset ; 

HIST_ENTRY *
next_history(void)
{
	HistEvent ev;

	if (history_offset >= history_length)
		return NULL;

	if (history(h, &ev, H_LAST) != 0)
		return NULL;

	history_offset++;
	return current_history();
}