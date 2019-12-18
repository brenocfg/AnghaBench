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
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  msleep (unsigned int) ; 
 scalar_t__ need_resched () ; 
 unsigned int rtas_busy_delay_time (int) ; 

unsigned int rtas_busy_delay(int status)
{
	unsigned int ms;

	might_sleep();
	ms = rtas_busy_delay_time(status);
	if (ms && need_resched())
		msleep(ms);

	return ms;
}