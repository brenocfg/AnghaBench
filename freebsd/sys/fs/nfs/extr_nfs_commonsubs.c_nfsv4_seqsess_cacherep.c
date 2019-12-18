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
typedef  size_t uint32_t ;
struct nfsslot {scalar_t__ nfssl_inprog; struct mbuf* nfssl_reply; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int NFSERR_REPLYFROMCACHE ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

void
nfsv4_seqsess_cacherep(uint32_t slotid, struct nfsslot *slots, int repstat,
   struct mbuf **rep)
{

	if (repstat == NFSERR_REPLYFROMCACHE) {
		*rep = slots[slotid].nfssl_reply;
		slots[slotid].nfssl_reply = NULL;
	} else {
		if (slots[slotid].nfssl_reply != NULL)
			m_freem(slots[slotid].nfssl_reply);
		slots[slotid].nfssl_reply = *rep;
	}
	slots[slotid].nfssl_inprog = 0;
}