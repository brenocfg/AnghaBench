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
 int /*<<< orphan*/  HRDBG (char*) ; 
 scalar_t__ fs_tbl_refresh ; 
 scalar_t__ fs_tick ; 
 int /*<<< orphan*/  refresh_storage_tbl (int) ; 
 scalar_t__ this_tick ; 

void
refresh_fs_tbl(void)
{

	if (fs_tick == 0 || this_tick - fs_tick >= fs_tbl_refresh) {
		refresh_storage_tbl(1);
		HRDBG("refresh DONE");
	}
}