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
 scalar_t__ V_ipport_firstauto ; 
 scalar_t__ V_ipport_lastauto ; 
 int /*<<< orphan*/  imax (int,int) ; 
 int imin (int /*<<< orphan*/ ,int) ; 
 int maxsockets ; 

__attribute__((used)) static int
tcptw_auto_size(void)
{
	int halfrange;

	/*
	 * Max out at half the ephemeral port range so that TIME_WAIT
	 * sockets don't tie up too many ephemeral ports.
	 */
	if (V_ipport_lastauto > V_ipport_firstauto)
		halfrange = (V_ipport_lastauto - V_ipport_firstauto) / 2;
	else
		halfrange = (V_ipport_firstauto - V_ipport_lastauto) / 2;
	/* Protect against goofy port ranges smaller than 32. */
	return (imin(imax(halfrange, 32), maxsockets / 5));
}