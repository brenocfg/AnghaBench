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
 int /*<<< orphan*/  V_pf_ip4_in_hook ; 
 int /*<<< orphan*/  V_pf_ip4_out_hook ; 
 int /*<<< orphan*/  V_pf_ip6_in_hook ; 
 int /*<<< orphan*/  V_pf_ip6_out_hook ; 
 scalar_t__ V_pf_pfil_hooked ; 
 int /*<<< orphan*/  pfil_remove_hook (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dehook_pf(void)
{

	if (V_pf_pfil_hooked == 0)
		return (0);

#ifdef INET
	pfil_remove_hook(V_pf_ip4_in_hook);
	pfil_remove_hook(V_pf_ip4_out_hook);
#endif
#ifdef INET6
	pfil_remove_hook(V_pf_ip6_in_hook);
	pfil_remove_hook(V_pf_ip6_out_hook);
#endif

	V_pf_pfil_hooked = 0;
	return (0);
}