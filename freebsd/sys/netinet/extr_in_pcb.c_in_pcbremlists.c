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
struct inpcbport {int inp_flags; int /*<<< orphan*/  phd_epoch_ctx; int /*<<< orphan*/  phd_pcblist; struct inpcbport* inp_phd; scalar_t__ inp_gencnt; struct inpcbinfo* inp_pcbinfo; } ;
struct inpcbinfo {int /*<<< orphan*/  ipi_count; scalar_t__ ipi_gencnt; } ;
struct inpcb {int inp_flags; int /*<<< orphan*/  phd_epoch_ctx; int /*<<< orphan*/  phd_pcblist; struct inpcb* inp_phd; scalar_t__ inp_gencnt; struct inpcbinfo* inp_pcbinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/ * CK_LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CK_LIST_REMOVE (struct inpcbport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INP_HASH_WLOCK (struct inpcbinfo*) ; 
 int /*<<< orphan*/  INP_HASH_WUNLOCK (struct inpcbinfo*) ; 
 int /*<<< orphan*/  INP_INFO_WLOCK_ASSERT (struct inpcbinfo*) ; 
 int INP_INHASHLIST ; 
 int /*<<< orphan*/  INP_LIST_WLOCK_ASSERT (struct inpcbinfo*) ; 
 int /*<<< orphan*/  INP_WLOCK_ASSERT (struct inpcbport*) ; 
 int /*<<< orphan*/  NET_EPOCH_ASSERT () ; 
 struct inpcbinfo V_tcbinfo ; 
 int /*<<< orphan*/  epoch_call (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_pcbgroup_remove (struct inpcbport*) ; 
 int /*<<< orphan*/  in_pcbremlbgrouphash (struct inpcbport*) ; 
 int /*<<< orphan*/  inp_hash ; 
 int /*<<< orphan*/  inp_list ; 
 int /*<<< orphan*/  inp_portlist ; 
 int /*<<< orphan*/  inpcbport_free ; 
 int /*<<< orphan*/  net_epoch_preempt ; 
 int /*<<< orphan*/  phd_hash ; 

__attribute__((used)) static void
in_pcbremlists(struct inpcb *inp)
{
	struct inpcbinfo *pcbinfo = inp->inp_pcbinfo;

#ifdef INVARIANTS
	if (pcbinfo == &V_tcbinfo) {
		NET_EPOCH_ASSERT();
	} else {
		INP_INFO_WLOCK_ASSERT(pcbinfo);
	}
#endif

	INP_WLOCK_ASSERT(inp);
	INP_LIST_WLOCK_ASSERT(pcbinfo);

	inp->inp_gencnt = ++pcbinfo->ipi_gencnt;
	if (inp->inp_flags & INP_INHASHLIST) {
		struct inpcbport *phd = inp->inp_phd;

		INP_HASH_WLOCK(pcbinfo);

		/* XXX: Only do if SO_REUSEPORT_LB set? */
		in_pcbremlbgrouphash(inp);

		CK_LIST_REMOVE(inp, inp_hash);
		CK_LIST_REMOVE(inp, inp_portlist);
		if (CK_LIST_FIRST(&phd->phd_pcblist) == NULL) {
			CK_LIST_REMOVE(phd, phd_hash);
			epoch_call(net_epoch_preempt, &phd->phd_epoch_ctx, inpcbport_free);
		}
		INP_HASH_WUNLOCK(pcbinfo);
		inp->inp_flags &= ~INP_INHASHLIST;
	}
	CK_LIST_REMOVE(inp, inp_list);
	pcbinfo->ipi_count--;
#ifdef PCBGROUP
	in_pcbgroup_remove(inp);
#endif
}