#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_6__ {scalar_t__ state; scalar_t__ seqlo; int /*<<< orphan*/  seqhi; } ;
struct TYPE_4__ {int /*<<< orphan*/  ptr; } ;
struct pf_state {scalar_t__ timeout; int /*<<< orphan*/  refs; int /*<<< orphan*/  tag; TYPE_3__ src; TYPE_2__** key; TYPE_1__ rule; } ;
struct pf_idhash {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * port; int /*<<< orphan*/ * addr; int /*<<< orphan*/  af; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct pf_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ PFTM_UNLINKED ; 
 int PF_ENTER_LOCKED ; 
 int /*<<< orphan*/  PF_HASHROW_ASSERT (struct pf_idhash*) ; 
 int /*<<< orphan*/  PF_HASHROW_LOCK (struct pf_idhash*) ; 
 int /*<<< orphan*/  PF_HASHROW_UNLOCK (struct pf_idhash*) ; 
 size_t PF_IDHASH (struct pf_state*) ; 
 size_t PF_SK_WIRE ; 
 scalar_t__ PF_TCPS_PROXY_DST ; 
 int /*<<< orphan*/  STATE_DEC_COUNTERS (struct pf_state*) ; 
 int TH_ACK ; 
 int TH_RST ; 
 struct pf_idhash* V_pf_idhash ; 
 int /*<<< orphan*/  V_pfsync_delete_state_ptr (struct pf_state*) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  pf_detach_state (struct pf_state*) ; 
 int pf_release_state (struct pf_state*) ; 
 int /*<<< orphan*/  pf_send_tcp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pf_src_tree_remove_state (struct pf_state*) ; 
 int /*<<< orphan*/  refcount_release (int /*<<< orphan*/ *) ; 

int
pf_unlink_state(struct pf_state *s, u_int flags)
{
	struct pf_idhash *ih = &V_pf_idhash[PF_IDHASH(s)];

	if ((flags & PF_ENTER_LOCKED) == 0)
		PF_HASHROW_LOCK(ih);
	else
		PF_HASHROW_ASSERT(ih);

	if (s->timeout == PFTM_UNLINKED) {
		/*
		 * State is being processed
		 * by pf_unlink_state() in
		 * an other thread.
		 */
		PF_HASHROW_UNLOCK(ih);
		return (0);	/* XXXGL: undefined actually */
	}

	if (s->src.state == PF_TCPS_PROXY_DST) {
		/* XXX wire key the right one? */
		pf_send_tcp(NULL, s->rule.ptr, s->key[PF_SK_WIRE]->af,
		    &s->key[PF_SK_WIRE]->addr[1],
		    &s->key[PF_SK_WIRE]->addr[0],
		    s->key[PF_SK_WIRE]->port[1],
		    s->key[PF_SK_WIRE]->port[0],
		    s->src.seqhi, s->src.seqlo + 1,
		    TH_RST|TH_ACK, 0, 0, 0, 1, s->tag, NULL);
	}

	LIST_REMOVE(s, entry);
	pf_src_tree_remove_state(s);

	if (V_pfsync_delete_state_ptr != NULL)
		V_pfsync_delete_state_ptr(s);

	STATE_DEC_COUNTERS(s);

	s->timeout = PFTM_UNLINKED;

	PF_HASHROW_UNLOCK(ih);

	pf_detach_state(s);
	/* pf_state_insert() initialises refs to 2, so we can never release the
	 * last reference here, only in pf_release_state(). */
	(void)refcount_release(&s->refs);

	return (pf_release_state(s));
}