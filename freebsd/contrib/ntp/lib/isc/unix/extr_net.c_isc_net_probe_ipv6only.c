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
typedef  int /*<<< orphan*/  isc_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_NOTFOUND ; 
 int /*<<< orphan*/  initialize_ipv6only () ; 
 int /*<<< orphan*/  ipv6only_result ; 

isc_result_t
isc_net_probe_ipv6only(void) {
#ifdef ISC_PLATFORM_HAVEIPV6
#ifdef WANT_IPV6
	initialize_ipv6only();
#else
	ipv6only_result = ISC_R_NOTFOUND;
#endif
#endif
	return (ipv6only_result);
}