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
typedef  int /*<<< orphan*/  u32 ;
struct nios2_clocksource {int /*<<< orphan*/  timer; } ;
struct clocksource {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  read_timersnapshot (int /*<<< orphan*/ *) ; 
 struct nios2_clocksource* to_nios2_clksource (struct clocksource*) ; 

__attribute__((used)) static u64 nios2_timer_read(struct clocksource *cs)
{
	struct nios2_clocksource *nios2_cs = to_nios2_clksource(cs);
	unsigned long flags;
	u32 count;

	local_irq_save(flags);
	count = read_timersnapshot(&nios2_cs->timer);
	local_irq_restore(flags);

	/* Counter is counting down */
	return ~count;
}