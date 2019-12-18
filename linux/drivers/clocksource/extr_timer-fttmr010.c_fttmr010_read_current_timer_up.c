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
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ TIMER2_COUNT ; 
 TYPE_1__* local_fttmr ; 
 unsigned long readl (scalar_t__) ; 

__attribute__((used)) static unsigned long fttmr010_read_current_timer_up(void)
{
	return readl(local_fttmr->base + TIMER2_COUNT);
}