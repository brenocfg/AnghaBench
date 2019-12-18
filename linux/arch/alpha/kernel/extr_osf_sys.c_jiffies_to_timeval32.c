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
struct timeval32 {unsigned long tv_usec; unsigned long tv_sec; } ;

/* Variables and functions */
 unsigned long HZ ; 

__attribute__((used)) static inline void
jiffies_to_timeval32(unsigned long jiffies, struct timeval32 *value)
{
	value->tv_usec = (jiffies % HZ) * (1000000L / HZ);
	value->tv_sec = jiffies / HZ;
}