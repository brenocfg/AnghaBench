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
 int /*<<< orphan*/  addr_wq ; 
 int hz ; 
 int jiffies ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  work ; 

__attribute__((used)) static void set_timeout(int time)
{
	int delay;	/* under FreeBSD ticks are 32-bit */

	delay = time - jiffies;
	if (delay <= 0)
		delay = 1;
	else if (delay > hz)
		delay = hz;

	mod_delayed_work(addr_wq, &work, delay);
}