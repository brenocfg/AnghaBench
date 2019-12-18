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
typedef  int /*<<< orphan*/  u32 ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOP_TMR_EN ; 
 int /*<<< orphan*/  read_tmr0 () ; 
 int /*<<< orphan*/  write_tmr0 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iop_shutdown(struct clock_event_device *evt)
{
	u32 tmr = read_tmr0();

	tmr &= ~IOP_TMR_EN;
	write_tmr0(tmr);
	return 0;
}