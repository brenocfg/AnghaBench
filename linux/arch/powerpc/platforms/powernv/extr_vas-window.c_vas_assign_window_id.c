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
struct ida {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ VAS_WINDOWS_PER_CHIP ; 
 int ida_alloc_max (struct ida*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 

__attribute__((used)) static int vas_assign_window_id(struct ida *ida)
{
	int winid = ida_alloc_max(ida, VAS_WINDOWS_PER_CHIP - 1, GFP_KERNEL);

	if (winid == -ENOSPC) {
		pr_err("Too many (%d) open windows\n", VAS_WINDOWS_PER_CHIP);
		return -EAGAIN;
	}

	return winid;
}