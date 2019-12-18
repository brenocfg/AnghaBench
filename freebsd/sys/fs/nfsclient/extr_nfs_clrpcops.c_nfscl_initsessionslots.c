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
struct nfsslot {int dummy; } ;
struct nfsclsession {scalar_t__ nfsess_slots; scalar_t__* nfsess_slotseq; TYPE_1__* nfsess_cbslots; } ;
struct TYPE_2__ {int /*<<< orphan*/ * nfssl_reply; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSBZERO (TYPE_1__*,int) ; 
 int NFSV4_CBSLOTS ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfscl_initsessionslots(struct nfsclsession *sep)
{
	int i;

	for (i = 0; i < NFSV4_CBSLOTS; i++) {
		if (sep->nfsess_cbslots[i].nfssl_reply != NULL)
			m_freem(sep->nfsess_cbslots[i].nfssl_reply);
		NFSBZERO(&sep->nfsess_cbslots[i], sizeof(struct nfsslot));
	}
	for (i = 0; i < 64; i++)
		sep->nfsess_slotseq[i] = 0;
	sep->nfsess_slots = 0;
}