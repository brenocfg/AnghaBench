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
struct inpcbport {int inp_refcount; int inp_flags; int /*<<< orphan*/  inp_pcbinfo; int /*<<< orphan*/  phd_epoch_ctx; int /*<<< orphan*/  phd_pcblist; struct inpcbport* inp_phd; int /*<<< orphan*/ * inp_ppcb; int /*<<< orphan*/ * inp_socket; } ;
struct inpcb {int inp_refcount; int inp_flags; int /*<<< orphan*/  inp_pcbinfo; int /*<<< orphan*/  phd_epoch_ctx; int /*<<< orphan*/  phd_pcblist; struct inpcb* inp_phd; int /*<<< orphan*/ * inp_ppcb; int /*<<< orphan*/ * inp_socket; } ;

/* Variables and functions */
 int /*<<< orphan*/ * CK_LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CK_LIST_REMOVE (struct inpcbport*,int /*<<< orphan*/ ) ; 
 int INP_DROPPED ; 
 int /*<<< orphan*/  INP_HASH_WLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INP_HASH_WUNLOCK (int /*<<< orphan*/ ) ; 
 int INP_INHASHLIST ; 
 int /*<<< orphan*/  INP_WLOCK_ASSERT (struct inpcbport*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  epoch_call (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_pcbgroup_remove (struct inpcbport*) ; 
 int /*<<< orphan*/  in_pcbremlbgrouphash (struct inpcbport*) ; 
 int /*<<< orphan*/  inp_hash ; 
 int /*<<< orphan*/  inp_portlist ; 
 int /*<<< orphan*/  inpcbport_free ; 
 int /*<<< orphan*/  net_epoch_preempt ; 
 int /*<<< orphan*/  phd_hash ; 

void
in_pcbdrop(struct inpcb *inp)
{

	INP_WLOCK_ASSERT(inp);
#ifdef INVARIANTS
	if (inp->inp_socket != NULL && inp->inp_ppcb != NULL)
		MPASS(inp->inp_refcount > 1);
#endif

	/*
	 * XXXRW: Possibly we should protect the setting of INP_DROPPED with
	 * the hash lock...?
	 */
	inp->inp_flags |= INP_DROPPED;
	if (inp->inp_flags & INP_INHASHLIST) {
		struct inpcbport *phd = inp->inp_phd;

		INP_HASH_WLOCK(inp->inp_pcbinfo);
		in_pcbremlbgrouphash(inp);
		CK_LIST_REMOVE(inp, inp_hash);
		CK_LIST_REMOVE(inp, inp_portlist);
		if (CK_LIST_FIRST(&phd->phd_pcblist) == NULL) {
			CK_LIST_REMOVE(phd, phd_hash);
			epoch_call(net_epoch_preempt, &phd->phd_epoch_ctx, inpcbport_free);
		}
		INP_HASH_WUNLOCK(inp->inp_pcbinfo);
		inp->inp_flags &= ~INP_INHASHLIST;
#ifdef PCBGROUP
		in_pcbgroup_remove(inp);
#endif
	}
}