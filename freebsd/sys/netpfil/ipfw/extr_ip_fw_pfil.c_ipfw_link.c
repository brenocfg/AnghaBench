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
struct pfil_link_args {int pa_flags; int /*<<< orphan*/  pa_hook; int /*<<< orphan*/  pa_head; int /*<<< orphan*/  pa_version; } ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_LINK 128 
 int PFIL_HEADPTR ; 
 int PFIL_HOOKPTR ; 
 int PFIL_IN ; 
 int PFIL_OUT ; 
 int PFIL_UNLINK ; 
 int /*<<< orphan*/  PFIL_VERSION ; 
 int /*<<< orphan*/  V_inet6_pfil_head ; 
 int /*<<< orphan*/  V_inet_pfil_head ; 
 int /*<<< orphan*/  V_ipfw_inet6_hook ; 
 int /*<<< orphan*/  V_ipfw_inet_hook ; 
 int /*<<< orphan*/  V_ipfw_link_hook ; 
 int /*<<< orphan*/  V_link_pfil_head ; 
 int pfil_link (struct pfil_link_args*) ; 

__attribute__((used)) static int
ipfw_link(int pf, bool unlink)
{
	struct pfil_link_args pla;

	pla.pa_version = PFIL_VERSION;
	pla.pa_flags = PFIL_IN | PFIL_OUT | PFIL_HEADPTR | PFIL_HOOKPTR;
	if (unlink)
		pla.pa_flags |= PFIL_UNLINK;

	switch (pf) {
	case AF_INET:
		pla.pa_head = V_inet_pfil_head;
		pla.pa_hook = V_ipfw_inet_hook;
		break;
#ifdef INET6
	case AF_INET6:
		pla.pa_head = V_inet6_pfil_head;
		pla.pa_hook = V_ipfw_inet6_hook;
		break;
#endif
	case AF_LINK:
		pla.pa_head = V_link_pfil_head;
		pla.pa_hook = V_ipfw_link_hook;
		break;
	}

	return (pfil_link(&pla));
}