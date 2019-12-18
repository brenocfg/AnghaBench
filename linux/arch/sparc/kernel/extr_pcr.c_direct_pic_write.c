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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static void direct_pic_write(unsigned long reg_num, u64 val)
{
	WARN_ON_ONCE(reg_num != 0);

	/* Blackbird errata workaround.  See commentary in
	 * arch/sparc64/kernel/smp.c:smp_percpu_timer_interrupt()
	 * for more information.
	 */
	__asm__ __volatile__("ba,pt	%%xcc, 99f\n\t"
			     " nop\n\t"
			     ".align	64\n"
			  "99:wr	%0, 0x0, %%pic\n\t"
			     "rd	%%pic, %%g0" : : "r" (val));
}