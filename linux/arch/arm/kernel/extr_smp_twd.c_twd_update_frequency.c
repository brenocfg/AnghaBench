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
 int /*<<< orphan*/  clockevents_update_freq (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  raw_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twd_evt ; 
 unsigned long twd_timer_rate ; 

__attribute__((used)) static void twd_update_frequency(void *new_rate)
{
	twd_timer_rate = *((unsigned long *) new_rate);

	clockevents_update_freq(raw_cpu_ptr(twd_evt), twd_timer_rate);
}