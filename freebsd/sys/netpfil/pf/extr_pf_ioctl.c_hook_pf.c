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
struct pfil_link_args {void* pa_hook; void* pa_head; void* pa_flags; void* pa_version; } ;
struct pfil_hook_args {char* pa_modname; char* pa_rulname; void* pa_flags; int /*<<< orphan*/  pa_func; int /*<<< orphan*/  pa_type; int /*<<< orphan*/ * pa_ruleset; void* pa_version; } ;

/* Variables and functions */
 void* PFIL_HEADPTR ; 
 void* PFIL_HOOKPTR ; 
 void* PFIL_IN ; 
 void* PFIL_OUT ; 
 int /*<<< orphan*/  PFIL_TYPE_IP4 ; 
 int /*<<< orphan*/  PFIL_TYPE_IP6 ; 
 void* PFIL_VERSION ; 
 void* V_inet6_pfil_head ; 
 void* V_inet_pfil_head ; 
 void* V_pf_ip4_in_hook ; 
 void* V_pf_ip4_out_hook ; 
 void* V_pf_ip6_in_hook ; 
 void* V_pf_ip6_out_hook ; 
 int V_pf_pfil_hooked ; 
 int /*<<< orphan*/  pf_check6_in ; 
 int /*<<< orphan*/  pf_check6_out ; 
 int /*<<< orphan*/  pf_check_in ; 
 int /*<<< orphan*/  pf_check_out ; 
 void* pfil_add_hook (struct pfil_hook_args*) ; 
 int /*<<< orphan*/  pfil_link (struct pfil_link_args*) ; 

__attribute__((used)) static int
hook_pf(void)
{
	struct pfil_hook_args pha;
	struct pfil_link_args pla;

	if (V_pf_pfil_hooked)
		return (0);

	pha.pa_version = PFIL_VERSION;
	pha.pa_modname = "pf";
	pha.pa_ruleset = NULL;

	pla.pa_version = PFIL_VERSION;

#ifdef INET
	pha.pa_type = PFIL_TYPE_IP4;
	pha.pa_func = pf_check_in;
	pha.pa_flags = PFIL_IN;
	pha.pa_rulname = "default-in";
	V_pf_ip4_in_hook = pfil_add_hook(&pha);
	pla.pa_flags = PFIL_IN | PFIL_HEADPTR | PFIL_HOOKPTR;
	pla.pa_head = V_inet_pfil_head;
	pla.pa_hook = V_pf_ip4_in_hook;
	(void)pfil_link(&pla);
	pha.pa_func = pf_check_out;
	pha.pa_flags = PFIL_OUT;
	pha.pa_rulname = "default-out";
	V_pf_ip4_out_hook = pfil_add_hook(&pha);
	pla.pa_flags = PFIL_OUT | PFIL_HEADPTR | PFIL_HOOKPTR;
	pla.pa_head = V_inet_pfil_head;
	pla.pa_hook = V_pf_ip4_out_hook;
	(void)pfil_link(&pla);
#endif
#ifdef INET6
	pha.pa_type = PFIL_TYPE_IP6;
	pha.pa_func = pf_check6_in;
	pha.pa_flags = PFIL_IN;
	pha.pa_rulname = "default-in6";
	V_pf_ip6_in_hook = pfil_add_hook(&pha);
	pla.pa_flags = PFIL_IN | PFIL_HEADPTR | PFIL_HOOKPTR;
	pla.pa_head = V_inet6_pfil_head;
	pla.pa_hook = V_pf_ip6_in_hook;
	(void)pfil_link(&pla);
	pha.pa_func = pf_check6_out;
	pha.pa_rulname = "default-out6";
	pha.pa_flags = PFIL_OUT;
	V_pf_ip6_out_hook = pfil_add_hook(&pha);
	pla.pa_flags = PFIL_OUT | PFIL_HEADPTR | PFIL_HOOKPTR;
	pla.pa_head = V_inet6_pfil_head;
	pla.pa_hook = V_pf_ip6_out_hook;
	(void)pfil_link(&pla);
#endif

	V_pf_pfil_hooked = 1;
	return (0);
}