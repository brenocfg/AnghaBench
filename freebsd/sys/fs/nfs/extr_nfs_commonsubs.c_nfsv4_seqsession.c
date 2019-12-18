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
typedef  size_t uint16_t ;
struct nfsslot {size_t nfssl_seq; int nfssl_inprog; struct mbuf* nfssl_reply; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int NFSERR_BADSLOT ; 
 int NFSERR_DELAY ; 
 int NFSERR_REPLYFROMCACHE ; 
 int NFSERR_SEQMISORDERED ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

int
nfsv4_seqsession(uint32_t seqid, uint32_t slotid, uint32_t highslot,
    struct nfsslot *slots, struct mbuf **reply, uint16_t maxslot)
{
	int error;

	error = 0;
	if (reply != NULL)
		*reply = NULL;
	if (slotid > maxslot)
		return (NFSERR_BADSLOT);
	if (seqid == slots[slotid].nfssl_seq) {
		/* A retry. */
		if (slots[slotid].nfssl_inprog != 0)
			error = NFSERR_DELAY;
		else if (slots[slotid].nfssl_reply != NULL) {
			if (reply != NULL) {
				*reply = slots[slotid].nfssl_reply;
				slots[slotid].nfssl_reply = NULL;
			}
			slots[slotid].nfssl_inprog = 1;
			error = NFSERR_REPLYFROMCACHE;
		} else
			/* No reply cached, so just do it. */
			slots[slotid].nfssl_inprog = 1;
	} else if ((slots[slotid].nfssl_seq + 1) == seqid) {
		if (slots[slotid].nfssl_reply != NULL)
			m_freem(slots[slotid].nfssl_reply);
		slots[slotid].nfssl_reply = NULL;
		slots[slotid].nfssl_inprog = 1;
		slots[slotid].nfssl_seq++;
	} else
		error = NFSERR_SEQMISORDERED;
	return (error);
}