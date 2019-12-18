#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct mbuf {int dummy; } ;
struct inpcbinfo {int /*<<< orphan*/  ipi_hashmask; struct inpcbhead* ipi_hashbase; } ;
struct inpcbhead {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct inpcb {int inp_flags; int inp_vflag; int /*<<< orphan*/  inp_fport; int /*<<< orphan*/  inp_lport; TYPE_1__ inp_faddr; int /*<<< orphan*/  in6p_faddr; struct inpcbinfo* inp_pcbinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK_LIST_INSERT_HEAD (struct inpcbhead*,struct inpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CK_LIST_REMOVE (struct inpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INP6_PCBHASHKEY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INP_HASH_WLOCK_ASSERT (struct inpcbinfo*) ; 
 int INP_INHASHLIST ; 
 int INP_IPV6 ; 
 size_t INP_PCBHASH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INP_WLOCK_ASSERT (struct inpcb*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  in_pcbgroup_update (struct inpcb*) ; 
 int /*<<< orphan*/  in_pcbgroup_update_mbuf (struct inpcb*,struct mbuf*) ; 
 int /*<<< orphan*/  inp_hash ; 

void
in_pcbrehash_mbuf(struct inpcb *inp, struct mbuf *m)
{
	struct inpcbinfo *pcbinfo = inp->inp_pcbinfo;
	struct inpcbhead *head;
	u_int32_t hashkey_faddr;

	INP_WLOCK_ASSERT(inp);
	INP_HASH_WLOCK_ASSERT(pcbinfo);

	KASSERT(inp->inp_flags & INP_INHASHLIST,
	    ("in_pcbrehash: !INP_INHASHLIST"));

#ifdef INET6
	if (inp->inp_vflag & INP_IPV6)
		hashkey_faddr = INP6_PCBHASHKEY(&inp->in6p_faddr);
	else
#endif
	hashkey_faddr = inp->inp_faddr.s_addr;

	head = &pcbinfo->ipi_hashbase[INP_PCBHASH(hashkey_faddr,
		inp->inp_lport, inp->inp_fport, pcbinfo->ipi_hashmask)];

	CK_LIST_REMOVE(inp, inp_hash);
	CK_LIST_INSERT_HEAD(head, inp, inp_hash);

#ifdef PCBGROUP
	if (m != NULL)
		in_pcbgroup_update_mbuf(inp, m);
	else
		in_pcbgroup_update(inp);
#endif
}