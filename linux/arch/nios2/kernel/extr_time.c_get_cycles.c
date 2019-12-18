#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cycles_t ;
struct TYPE_3__ {scalar_t__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  cs; TYPE_1__ timer; } ;

/* Variables and functions */
 TYPE_2__ nios2_cs ; 
 int /*<<< orphan*/  nios2_timer_read (int /*<<< orphan*/ *) ; 

cycles_t get_cycles(void)
{
	/* Only read timer if it has been initialized */
	if (nios2_cs.timer.base)
		return nios2_timer_read(&nios2_cs.cs);
	return 0;
}