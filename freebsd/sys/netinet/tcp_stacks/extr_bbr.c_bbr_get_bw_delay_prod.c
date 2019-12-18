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
typedef  int uint64_t ;

/* Variables and functions */
 int USECS_IN_SECOND ; 

__attribute__((used)) static uint64_t
bbr_get_bw_delay_prod(uint64_t rtt, uint64_t bw) {
	/*
	 * Calculate the bytes in flight needed given the bw (in bytes per
	 * second) and the specifyed rtt in useconds. We need to put out the
	 * returned value per RTT to match that rate. Gain will normaly
	 * raise it up from there.
	 *
	 * This should not overflow as long as the bandwidth is below 1
	 * TByte per second (bw < 10**12 = 2**40) and the rtt is smaller
	 * than 1000 seconds (rtt < 10**3 * 10**6 = 10**9 = 2**30).
	 */
	uint64_t usec_per_sec;

	usec_per_sec = USECS_IN_SECOND;
	return ((rtt * bw) / usec_per_sec);
}