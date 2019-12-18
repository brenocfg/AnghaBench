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
struct os_reltime {unsigned int usec; scalar_t__ sec; } ;
typedef  unsigned int os_time_t ;

/* Variables and functions */

void calculate_update_time(const struct os_reltime *fetch_time,
			   unsigned int age_ms,
			   struct os_reltime *update_time)
{
	os_time_t usec;

	update_time->sec = fetch_time->sec;
	update_time->usec = fetch_time->usec;
	update_time->sec -= age_ms / 1000;
	usec = (age_ms % 1000) * 1000;
	if (update_time->usec < usec) {
		update_time->sec--;
		update_time->usec += 1000000;
	}
	update_time->usec -= usec;
}