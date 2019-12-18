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
#define  RIC_FLUSH_ALL 130 
#define  RIC_FLUSH_PWC 129 
#define  RIC_FLUSH_TLB 128 
 int /*<<< orphan*/  __tlbie_pid (unsigned long,int const) ; 
 int /*<<< orphan*/  fixup_tlbie_pid (unsigned long) ; 

__attribute__((used)) static inline void _tlbie_pid(unsigned long pid, unsigned long ric)
{
	asm volatile("ptesync": : :"memory");

	/*
	 * Workaround the fact that the "ric" argument to __tlbie_pid
	 * must be a compile-time contraint to match the "i" constraint
	 * in the asm statement.
	 */
	switch (ric) {
	case RIC_FLUSH_TLB:
		__tlbie_pid(pid, RIC_FLUSH_TLB);
		fixup_tlbie_pid(pid);
		break;
	case RIC_FLUSH_PWC:
		__tlbie_pid(pid, RIC_FLUSH_PWC);
		break;
	case RIC_FLUSH_ALL:
	default:
		__tlbie_pid(pid, RIC_FLUSH_ALL);
		fixup_tlbie_pid(pid);
	}
	asm volatile("eieio; tlbsync; ptesync": : :"memory");
}