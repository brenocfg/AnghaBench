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
 int getnanotime () ; 
 int tr2tls_us_start_process ; 

void tr2tls_start_process_clock(void)
{
	if (tr2tls_us_start_process)
		return;

	/*
	 * Keep the absolute start time of the process (i.e. the main
	 * process) in a fixed variable since other threads need to
	 * access it.  This allows them to do that without a lock on
	 * main thread's array data (because of reallocs).
	 */
	tr2tls_us_start_process = getnanotime() / 1000;
}