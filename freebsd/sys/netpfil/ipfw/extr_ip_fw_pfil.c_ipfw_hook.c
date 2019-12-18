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
struct pfil_hook_args {int pa_flags; char* pa_modname; char* pa_rulname; int /*<<< orphan*/  pa_type; void* pa_func; int /*<<< orphan*/ * pa_ruleset; int /*<<< orphan*/  pa_version; } ;
typedef  int /*<<< orphan*/  pfil_hook_t ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_LINK 128 
 int PFIL_IN ; 
 int PFIL_MEMPTR ; 
 int PFIL_OUT ; 
 int /*<<< orphan*/  PFIL_TYPE_ETHERNET ; 
 int /*<<< orphan*/  PFIL_TYPE_IP4 ; 
 int /*<<< orphan*/  PFIL_TYPE_IP6 ; 
 int /*<<< orphan*/  PFIL_VERSION ; 
 int /*<<< orphan*/  V_ipfw_inet6_hook ; 
 int /*<<< orphan*/  V_ipfw_inet_hook ; 
 int /*<<< orphan*/  V_ipfw_link_hook ; 
 void* ipfw_check_frame ; 
 void* ipfw_check_packet ; 
 int /*<<< orphan*/  pfil_add_hook (struct pfil_hook_args*) ; 

__attribute__((used)) static void
ipfw_hook(int pf)
{
	struct pfil_hook_args pha;
	pfil_hook_t *h;

	pha.pa_version = PFIL_VERSION;
	pha.pa_flags = PFIL_IN | PFIL_OUT;
	pha.pa_modname = "ipfw";
	pha.pa_ruleset = NULL;

	switch (pf) {
	case AF_INET:
		pha.pa_func = ipfw_check_packet;
		pha.pa_type = PFIL_TYPE_IP4;
		pha.pa_rulname = "default";
		h = &V_ipfw_inet_hook;
		break;
#ifdef INET6
	case AF_INET6:
		pha.pa_func = ipfw_check_packet;
		pha.pa_type = PFIL_TYPE_IP6;
		pha.pa_rulname = "default6";
		h = &V_ipfw_inet6_hook;
		break;
#endif
	case AF_LINK:
		pha.pa_func = ipfw_check_frame;
		pha.pa_type = PFIL_TYPE_ETHERNET;
		pha.pa_rulname = "default-link";
		pha.pa_flags |= PFIL_MEMPTR;
		h = &V_ipfw_link_hook;
		break;
	}

	*h = pfil_add_hook(&pha);
}