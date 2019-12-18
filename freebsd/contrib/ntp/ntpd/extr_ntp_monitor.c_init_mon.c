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

/* Variables and functions */
 int /*<<< orphan*/  INIT_DLIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MON_OFF ; 
 int /*<<< orphan*/  mon_enabled ; 
 int /*<<< orphan*/  mon_mru_list ; 
 int /*<<< orphan*/  mru ; 

void
init_mon(void)
{
	/*
	 * Don't do much of anything here.  We don't allocate memory
	 * until mon_start().
	 */
	mon_enabled = MON_OFF;
	INIT_DLIST(mon_mru_list, mru);
}