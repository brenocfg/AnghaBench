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
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  TIF_ISOLATE_BP_GUEST ; 
 int /*<<< orphan*/  set_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_facility (int) ; 

int s390_isolate_bp_guest(void)
{
	if (!test_facility(82))
		return -EOPNOTSUPP;
	set_thread_flag(TIF_ISOLATE_BP_GUEST);
	return 0;
}