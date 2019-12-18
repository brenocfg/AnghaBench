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
typedef  int time_t ;

/* Variables and functions */
 int cp0_count_get () ; 

time_t
time(time_t *tloc)
{

	/* We can't provide time since UTC, so just provide time since boot. */
	return (cp0_count_get() / 100000000);
}