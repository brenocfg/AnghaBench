#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* nfsess_cbslots; int /*<<< orphan*/  nfsess_mtx; } ;
struct nfsclds {TYPE_2__ nfsclds_sess; int /*<<< orphan*/  nfsclds_mtx; struct nfsclds* nfsclds_sockp; struct nfsclds* nr_nam; int /*<<< orphan*/  nr_mtx; int /*<<< orphan*/  nr_cred; } ;
struct TYPE_3__ {int /*<<< orphan*/ * nfssl_reply; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NFSCLDS ; 
 int /*<<< orphan*/  M_NFSSOCKREQ ; 
 int /*<<< orphan*/  M_SONAME ; 
 int /*<<< orphan*/  NFSFREECRED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSFREEMUTEX (int /*<<< orphan*/ *) ; 
 int NFSV4_CBSLOTS ; 
 int /*<<< orphan*/  free (struct nfsclds*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

void
nfscl_freenfsclds(struct nfsclds *dsp)
{
	int i;

	if (dsp == NULL)
		return;
	if (dsp->nfsclds_sockp != NULL) {
		NFSFREECRED(dsp->nfsclds_sockp->nr_cred);
		NFSFREEMUTEX(&dsp->nfsclds_sockp->nr_mtx);
		free(dsp->nfsclds_sockp->nr_nam, M_SONAME);
		free(dsp->nfsclds_sockp, M_NFSSOCKREQ);
	}
	NFSFREEMUTEX(&dsp->nfsclds_mtx);
	NFSFREEMUTEX(&dsp->nfsclds_sess.nfsess_mtx);
	for (i = 0; i < NFSV4_CBSLOTS; i++) {
		if (dsp->nfsclds_sess.nfsess_cbslots[i].nfssl_reply != NULL)
			m_freem(
			    dsp->nfsclds_sess.nfsess_cbslots[i].nfssl_reply);
	}
	free(dsp, M_NFSCLDS);
}