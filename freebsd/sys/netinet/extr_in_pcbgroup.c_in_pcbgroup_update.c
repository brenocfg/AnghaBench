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
struct inpcbinfo {int dummy; } ;
struct inpcbgroup {int dummy; } ;
struct inpcb {int inp_flags2; int inp_flags; int inp_vflag; struct inpcbinfo* inp_pcbinfo; } ;

/* Variables and functions */
 int INP_DROPPED ; 
 int INP_IPV6 ; 
 int INP_PCBGROUPWILD ; 
 int /*<<< orphan*/  INP_WLOCK_ASSERT (struct inpcb*) ; 
 struct inpcbgroup* in6_pcbgroup_byinpcb (struct inpcb*) ; 
 struct inpcbgroup* in_pcbgroup_byinpcb (struct inpcb*) ; 
 int /*<<< orphan*/  in_pcbgroup_enabled (struct inpcbinfo*) ; 
 int /*<<< orphan*/  in_pcbgroup_update_internal (struct inpcbinfo*,struct inpcbgroup*,struct inpcb*) ; 
 int /*<<< orphan*/  in_pcbwild_update_internal (struct inpcb*) ; 

void
in_pcbgroup_update(struct inpcb *inp)
{
	struct inpcbinfo *pcbinfo;
	struct inpcbgroup *newpcbgroup;

	INP_WLOCK_ASSERT(inp);

	pcbinfo = inp->inp_pcbinfo;
	if (!in_pcbgroup_enabled(pcbinfo))
		return;

	in_pcbwild_update_internal(inp);
	if (!(inp->inp_flags2 & INP_PCBGROUPWILD) &&
	    !(inp->inp_flags & INP_DROPPED)) {
#ifdef INET6
		if (inp->inp_vflag & INP_IPV6)
			newpcbgroup = in6_pcbgroup_byinpcb(inp);
		else
#endif
			newpcbgroup = in_pcbgroup_byinpcb(inp);
	} else
		newpcbgroup = NULL;
	in_pcbgroup_update_internal(pcbinfo, newpcbgroup, inp);
}