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
struct inpcbgroup {int dummy; } ;
struct inpcb {int inp_flags2; struct inpcbgroup* inp_pcbgroup; int /*<<< orphan*/  inp_pcbinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK_LIST_REMOVE (struct inpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INP_GROUP_LOCK (struct inpcbgroup*) ; 
 int /*<<< orphan*/  INP_GROUP_UNLOCK (struct inpcbgroup*) ; 
 int INP_PCBGROUPWILD ; 
 int /*<<< orphan*/  INP_WLOCK_ASSERT (struct inpcb*) ; 
 int /*<<< orphan*/  in_pcbgroup_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_pcbwild_remove (struct inpcb*) ; 
 int /*<<< orphan*/  inp_pcbgrouphash ; 

void
in_pcbgroup_remove(struct inpcb *inp)
{
	struct inpcbgroup *pcbgroup;

	INP_WLOCK_ASSERT(inp);

	if (!in_pcbgroup_enabled(inp->inp_pcbinfo))
		return;

	if (inp->inp_flags2 & INP_PCBGROUPWILD)
		in_pcbwild_remove(inp);

	pcbgroup = inp->inp_pcbgroup;
	if (pcbgroup != NULL) {
		INP_GROUP_LOCK(pcbgroup);
		CK_LIST_REMOVE(inp, inp_pcbgrouphash);
		inp->inp_pcbgroup = NULL;
		INP_GROUP_UNLOCK(pcbgroup);
	}
}