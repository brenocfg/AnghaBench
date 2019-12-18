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
typedef  int u_int16_t ;

/* Variables and functions */
 int IPPORT_HIFIRSTAUTO ; 
 int IPPORT_HILASTAUTO ; 
 int arc4random () ; 

u_int16_t
pick_proxy_port(void)
{
	return (IPPORT_HIFIRSTAUTO + (arc4random() %
	    (IPPORT_HILASTAUTO - IPPORT_HIFIRSTAUTO)));
}