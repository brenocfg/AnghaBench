#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* is_user_mode ) () ;scalar_t__ (* is_in_guest ) () ;} ;

/* Variables and functions */
 int PERF_RECORD_MISC_GUEST_KERNEL ; 
 int PERF_RECORD_MISC_GUEST_USER ; 
 int PERF_RECORD_MISC_KERNEL ; 
 int PERF_RECORD_MISC_USER ; 
 TYPE_1__* perf_guest_cbs ; 
 scalar_t__ stub1 () ; 
 scalar_t__ stub2 () ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

unsigned long perf_misc_flags(struct pt_regs *regs)
{
	int misc = 0;

	/* However, NDS32 does not support virtualization */
	if (perf_guest_cbs && perf_guest_cbs->is_in_guest()) {
		if (perf_guest_cbs->is_user_mode())
			misc |= PERF_RECORD_MISC_GUEST_USER;
		else
			misc |= PERF_RECORD_MISC_GUEST_KERNEL;
	} else {
		if (user_mode(regs))
			misc |= PERF_RECORD_MISC_USER;
		else
			misc |= PERF_RECORD_MISC_KERNEL;
	}

	return misc;
}