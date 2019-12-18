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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ last_update_timer; int /*<<< orphan*/  system_timer; } ;

/* Variables and functions */
 TYPE_1__ S390_lowcore ; 

__attribute__((used)) static inline void set_vtimer(u64 expires)
{
	u64 timer;

	asm volatile(
		"	stpt	%0\n"	/* Store current cpu timer value */
		"	spt	%1"	/* Set new value imm. afterwards */
		: "=Q" (timer) : "Q" (expires));
	S390_lowcore.system_timer += S390_lowcore.last_update_timer - timer;
	S390_lowcore.last_update_timer = expires;
}