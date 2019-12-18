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
 int OF_milliseconds () ; 

time_t
time(time_t *tloc)
{
	int secs;

	secs = OF_milliseconds() / 1000;
	if (tloc)
		*tloc = secs;
	return secs;
}