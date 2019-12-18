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
struct secpolicy {int /*<<< orphan*/  spidx; } ;
struct inpcb {TYPE_1__* inp_sp; } ;
struct TYPE_2__ {int flags; struct secpolicy* sp_out; struct secpolicy* sp_in; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int INP_INBOUND_POLICY ; 
 int /*<<< orphan*/  INP_LOCK_ASSERT (struct inpcb*) ; 
 int INP_OUTBOUND_POLICY ; 
 int /*<<< orphan*/  INP_WLOCK_ASSERT (struct inpcb*) ; 
 int /*<<< orphan*/  IPSEC_ASSERT (int,char*) ; 
 int /*<<< orphan*/  IPSEC_DIR_INBOUND ; 
 int /*<<< orphan*/  IPSEC_DIR_OUTBOUND ; 
 struct secpolicy* ipsec_deepcopy_pcbpolicy (struct secpolicy*) ; 
 int /*<<< orphan*/  ipsec_setspidx_inpcb (struct inpcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_freesp (struct secpolicy**) ; 

int
ipsec_copy_pcbpolicy(struct inpcb *old, struct inpcb *new)
{
	struct secpolicy *sp;

	/*
	 * old->inp_sp can be NULL if PCB was created when an IPsec
	 * support was unavailable. This is not an error, we don't have
	 * policies in this PCB, so nothing to copy.
	 */
	if (old->inp_sp == NULL)
		return (0);

	IPSEC_ASSERT(new->inp_sp != NULL, ("new inp_sp is NULL"));
	IPSEC_ASSERT((new->inp_sp->flags & (
	    INP_INBOUND_POLICY | INP_OUTBOUND_POLICY)) == 0,
	    ("new PCB already has configured policies"));
	INP_WLOCK_ASSERT(new);
	INP_LOCK_ASSERT(old);

	if (old->inp_sp->flags & INP_INBOUND_POLICY) {
		sp = ipsec_deepcopy_pcbpolicy(old->inp_sp->sp_in);
		if (sp == NULL)
			return (ENOBUFS);
		ipsec_setspidx_inpcb(new, &sp->spidx, IPSEC_DIR_INBOUND);
		if (new->inp_sp->sp_in != NULL)
			key_freesp(&new->inp_sp->sp_in);
		new->inp_sp->sp_in = sp;
		new->inp_sp->flags |= INP_INBOUND_POLICY;
	}
	if (old->inp_sp->flags & INP_OUTBOUND_POLICY) {
		sp = ipsec_deepcopy_pcbpolicy(old->inp_sp->sp_out);
		if (sp == NULL)
			return (ENOBUFS);
		ipsec_setspidx_inpcb(new, &sp->spidx, IPSEC_DIR_OUTBOUND);
		if (new->inp_sp->sp_out != NULL)
			key_freesp(&new->inp_sp->sp_out);
		new->inp_sp->sp_out = sp;
		new->inp_sp->flags |= INP_OUTBOUND_POLICY;
	}
	return (0);
}