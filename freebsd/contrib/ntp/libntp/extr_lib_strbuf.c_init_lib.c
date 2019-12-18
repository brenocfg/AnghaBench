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
 scalar_t__ ISC_R_SUCCESS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  init_systime () ; 
 int ipv4_works ; 
 int ipv6_works ; 
 scalar_t__ isc_net_probeipv4 () ; 
 scalar_t__ isc_net_probeipv6 () ; 
 scalar_t__ lib_inited ; 

void
init_lib(void)
{
	if (lib_inited)
		return;
	ipv4_works = (ISC_R_SUCCESS == isc_net_probeipv4());
	ipv6_works = (ISC_R_SUCCESS == isc_net_probeipv6());
	init_systime();
	lib_inited = TRUE;
}