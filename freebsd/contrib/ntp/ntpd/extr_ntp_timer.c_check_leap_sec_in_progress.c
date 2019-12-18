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
struct TYPE_3__ {int ddist; scalar_t__ tai_diff; } ;
typedef  TYPE_1__ leap_result_t ;

/* Variables and functions */
 int leap_sec_in_progress ; 
 int /*<<< orphan*/  set_sys_leap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sys_leap ; 

__attribute__((used)) static void
check_leap_sec_in_progress( const leap_result_t *lsdata ) {
	int prv_leap_sec_in_progress = leap_sec_in_progress;
	leap_sec_in_progress = lsdata->tai_diff && (lsdata->ddist < 3);

	/* if changed we may have to update the leap status sent to clients */
	if (leap_sec_in_progress != prv_leap_sec_in_progress)
		set_sys_leap(sys_leap);
}