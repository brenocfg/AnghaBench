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
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_LINK 128 
 int /*<<< orphan*/  V_ipfw_inet6_hook ; 
 int /*<<< orphan*/  V_ipfw_inet_hook ; 
 int /*<<< orphan*/  V_ipfw_link_hook ; 
 int /*<<< orphan*/  pfil_remove_hook (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ipfw_unhook(int pf)
{

	switch (pf) {
	case AF_INET:
		pfil_remove_hook(V_ipfw_inet_hook);
		break;
#ifdef INET6
	case AF_INET6:
		pfil_remove_hook(V_ipfw_inet6_hook);
		break;
#endif
	case AF_LINK:
		pfil_remove_hook(V_ipfw_link_hook);
		break;
	}
}