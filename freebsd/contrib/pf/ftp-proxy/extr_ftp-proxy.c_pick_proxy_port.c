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
typedef  scalar_t__ u_int16_t ;

/* Variables and functions */
 scalar_t__ IPPORT_HIFIRSTAUTO ; 
 scalar_t__ IPPORT_HILASTAUTO ; 
 scalar_t__ arc4random_uniform (scalar_t__) ; 

u_int16_t
pick_proxy_port(void)
{
	/* Random should be good enough for avoiding port collisions. */
	return (IPPORT_HIFIRSTAUTO +
	    arc4random_uniform(IPPORT_HILASTAUTO - IPPORT_HIFIRSTAUTO));
}