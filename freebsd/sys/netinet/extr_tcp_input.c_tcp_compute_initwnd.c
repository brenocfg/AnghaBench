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
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ V_tcp_do_rfc3390 ; 
 int V_tcp_initcwnd_segments ; 
 int /*<<< orphan*/  max (int,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 

uint32_t
tcp_compute_initwnd(uint32_t maxseg)
{
	/*
	 * Calculate the Initial Window, also used as Restart Window
	 *
	 * RFC5681 Section 3.1 specifies the default conservative values.
	 * RFC3390 specifies slightly more aggressive values.
	 * RFC6928 increases it to ten segments.
	 * Support for user specified value for initial flight size.
	 */
	if (V_tcp_initcwnd_segments)
		return min(V_tcp_initcwnd_segments * maxseg,
		    max(2 * maxseg, V_tcp_initcwnd_segments * 1460));
	else if (V_tcp_do_rfc3390)
		return min(4 * maxseg, max(2 * maxseg, 4380));
	else {
		/* Per RFC5681 Section 3.1 */
		if (maxseg > 2190)
			return (2 * maxseg);
		else if (maxseg > 1095)
			return (3 * maxseg);
		else
			return (4 * maxseg);
	}
}