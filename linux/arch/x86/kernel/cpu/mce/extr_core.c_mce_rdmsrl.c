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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  finished; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ __this_cpu_read (int /*<<< orphan*/ ) ; 
 TYPE_1__ injectm ; 
 int msr_to_offset (int /*<<< orphan*/ ) ; 
 scalar_t__ rdmsrl_safe (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ this_cpu_ptr (TYPE_1__*) ; 

__attribute__((used)) static u64 mce_rdmsrl(u32 msr)
{
	u64 v;

	if (__this_cpu_read(injectm.finished)) {
		int offset = msr_to_offset(msr);

		if (offset < 0)
			return 0;
		return *(u64 *)((char *)this_cpu_ptr(&injectm) + offset);
	}

	if (rdmsrl_safe(msr, &v)) {
		WARN_ONCE(1, "mce: Unable to read MSR 0x%x!\n", msr);
		/*
		 * Return zero in case the access faulted. This should
		 * not happen normally but can happen if the CPU does
		 * something weird, or if the code is buggy.
		 */
		v = 0;
	}

	return v;
}