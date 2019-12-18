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
typedef  int u32 ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int IOP_TMR_EN ; 
 int IOP_TMR_RELOAD ; 
 int read_tmr0 () ; 
 scalar_t__ ticks_per_jiffy ; 
 int /*<<< orphan*/  write_tcr0 (scalar_t__) ; 
 int /*<<< orphan*/  write_tmr0 (int) ; 
 int /*<<< orphan*/  write_trr0 (scalar_t__) ; 

__attribute__((used)) static int iop_set_periodic(struct clock_event_device *evt)
{
	u32 tmr = read_tmr0();

	write_tmr0(tmr & ~IOP_TMR_EN);
	write_tcr0(ticks_per_jiffy - 1);
	write_trr0(ticks_per_jiffy - 1);
	tmr |= (IOP_TMR_RELOAD | IOP_TMR_EN);

	write_tmr0(tmr);
	return 0;
}