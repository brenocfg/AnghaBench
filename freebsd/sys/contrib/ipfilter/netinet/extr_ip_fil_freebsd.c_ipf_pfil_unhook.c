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
 int /*<<< orphan*/  V_ipf_inet6_hook ; 
 int /*<<< orphan*/  V_ipf_inet_hook ; 
 int /*<<< orphan*/  pfil_remove_hook (int /*<<< orphan*/ ) ; 

int ipf_pfil_unhook(void) {

	pfil_remove_hook(V_ipf_inet_hook);

#ifdef USE_INET6
	pfil_remove_hook(V_ipf_inet6_hook);
#endif

	return (0);
}