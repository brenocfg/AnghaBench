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
typedef  int u_long ;

/* Variables and functions */
 int PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSENTER () ; 
 int /*<<< orphan*/  TSEXIT () ; 
 int /*<<< orphan*/  clock ; 
 int /*<<< orphan*/  cpu_spinwait () ; 
 int rd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_pin () ; 
 int /*<<< orphan*/  sched_unpin () ; 
 int /*<<< orphan*/  tick ; 

void
DELAY(int usec)
{
	u_long end;

	if (usec < 0)
		return;
	TSENTER();

	/*
	 * We avoid being migrated to another CPU with a possibly
	 * unsynchronized TICK timer while spinning.
	 */
	sched_pin();

	end = rd(tick) + (u_long)usec * PCPU_GET(clock) / 1000000;
	while (rd(tick) < end)
		cpu_spinwait();

	sched_unpin();
	TSEXIT();
}