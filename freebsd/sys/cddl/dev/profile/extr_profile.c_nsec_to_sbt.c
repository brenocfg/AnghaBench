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
typedef  int sbintime_t ;
typedef  int hrtime_t ;

/* Variables and functions */
 int NANOSEC ; 

__attribute__((used)) static sbintime_t
nsec_to_sbt(hrtime_t nsec)
{
	time_t sec;

	/*
	 * We need to calculate nsec * 2^32 / 10^9
	 * Seconds and nanoseconds are split to avoid overflow.
	 */
	sec = nsec / NANOSEC;
	nsec = nsec % NANOSEC;
	return (((sbintime_t)sec << 32) | ((sbintime_t)nsec << 32) / NANOSEC);
}