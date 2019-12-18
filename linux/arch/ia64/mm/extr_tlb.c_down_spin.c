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
struct spinaphore {unsigned long serve; int /*<<< orphan*/  ticket; } ;

/* Variables and functions */
 int /*<<< orphan*/  acq ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long ia64_fetchadd (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ia64_invala () ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static inline void down_spin(struct spinaphore *ss)
{
	unsigned long t = ia64_fetchadd(1, &ss->ticket, acq), serve;

	if (time_before(t, ss->serve))
		return;

	ia64_invala();

	for (;;) {
		asm volatile ("ld8.c.nc %0=[%1]" : "=r"(serve) : "r"(&ss->serve) : "memory");
		if (time_before(t, serve))
			return;
		cpu_relax();
	}
}