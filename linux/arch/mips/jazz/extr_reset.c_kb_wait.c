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
 int HZ ; 
 int jazz_read_status () ; 
 unsigned long jiffies ; 
 scalar_t__ time_before_eq (unsigned long,unsigned long) ; 

__attribute__((used)) static inline void kb_wait(void)
{
	unsigned long start = jiffies;
	unsigned long timeout = start + HZ/2;

	do {
		if (! (jazz_read_status() & 0x02))
			return;
	} while (time_before_eq(jiffies, timeout));
}