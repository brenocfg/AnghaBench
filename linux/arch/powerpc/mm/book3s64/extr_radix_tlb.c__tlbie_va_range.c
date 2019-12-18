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
 int /*<<< orphan*/  RIC_FLUSH_PWC ; 
 int /*<<< orphan*/  __tlbie_pid (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __tlbie_va_range (unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static inline void _tlbie_va_range(unsigned long start, unsigned long end,
				    unsigned long pid, unsigned long page_size,
				    unsigned long psize, bool also_pwc)
{
	asm volatile("ptesync": : :"memory");
	if (also_pwc)
		__tlbie_pid(pid, RIC_FLUSH_PWC);
	__tlbie_va_range(start, end, pid, page_size, psize);
	asm volatile("eieio; tlbsync; ptesync": : :"memory");
}