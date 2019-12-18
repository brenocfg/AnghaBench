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
 int flush_needed ; 
 scalar_t__ mytime_now () ; 
 scalar_t__ next_flush ; 
 scalar_t__ opt_flush_timeout ; 
 scalar_t__ start_time ; 

extern void
mytime_set_start_time(void)
{
	start_time = mytime_now();
	next_flush = start_time + opt_flush_timeout;
	flush_needed = false;
	return;
}