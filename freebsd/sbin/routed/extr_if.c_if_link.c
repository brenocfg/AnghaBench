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
struct interface {int int_if_flags; int int_state; struct interface* int_nhash; struct interface** int_nhash_prev; int /*<<< orphan*/  int_name; struct interface* int_bhash; struct interface** int_bhash_prev; int /*<<< orphan*/  int_brdaddr; struct interface* int_ahash; struct interface** int_ahash_prev; int /*<<< orphan*/  int_addr; } ;

/* Variables and functions */
 struct interface** AHASH (int /*<<< orphan*/ ) ; 
 struct interface** BHASH (int /*<<< orphan*/ ) ; 
 int IFF_BROADCAST ; 
 int IS_ALIAS ; 
 int IS_REMOTE ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct interface*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet ; 
 int /*<<< orphan*/  int_list ; 
 struct interface** nhash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remote_if ; 
 int /*<<< orphan*/  remote_list ; 

void
if_link(struct interface *ifp)
{
	struct interface **hifp;

	LIST_INSERT_HEAD(&ifnet, ifp, int_list);

	hifp = AHASH(ifp->int_addr);
	ifp->int_ahash_prev = hifp;
	if ((ifp->int_ahash = *hifp) != NULL)
		(*hifp)->int_ahash_prev = &ifp->int_ahash;
	*hifp = ifp;

	if (ifp->int_if_flags & IFF_BROADCAST) {
		hifp = BHASH(ifp->int_brdaddr);
		ifp->int_bhash_prev = hifp;
		if ((ifp->int_bhash = *hifp) != NULL)
			(*hifp)->int_bhash_prev = &ifp->int_bhash;
		*hifp = ifp;
	}

	if (ifp->int_state & IS_REMOTE)
		LIST_INSERT_HEAD(&remote_if, ifp, remote_list);

	hifp = nhash(ifp->int_name);
	if (ifp->int_state & IS_ALIAS) {
		/* put aliases on the end of the hash chain */
		while (*hifp != NULL)
			hifp = &(*hifp)->int_nhash;
	}
	ifp->int_nhash_prev = hifp;
	if ((ifp->int_nhash = *hifp) != NULL)
		(*hifp)->int_nhash_prev = &ifp->int_nhash;
	*hifp = ifp;
}