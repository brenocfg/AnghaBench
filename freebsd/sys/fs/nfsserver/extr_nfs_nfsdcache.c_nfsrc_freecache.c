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
struct nfsrvcache {int rc_flag; scalar_t__ rc_acked; int /*<<< orphan*/  rc_reply; int /*<<< orphan*/  rc_sockref; } ;
struct nfsrchash_bucket {int /*<<< orphan*/  mtx; } ;
struct TYPE_2__ {int /*<<< orphan*/  srvcache_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct nfsrvcache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NFSRVCACHE ; 
 struct nfsrchash_bucket* NFSRCAHASH (int /*<<< orphan*/ ) ; 
 scalar_t__ RC_NO_ACK ; 
 scalar_t__ RC_NO_SEQ ; 
 int RC_REPMBUF ; 
 int RC_UDP ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct nfsrvcache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (struct nfsrvcache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_freem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsrc_tcpsavedreplies ; 
 int /*<<< orphan*/  nfsrc_udpcachesize ; 
 int /*<<< orphan*/  nfsrc_wanted (struct nfsrvcache*) ; 
 int /*<<< orphan*/  nfsrvudplru ; 
 TYPE_1__ nfsstatsv1 ; 
 int /*<<< orphan*/  rc_ahash ; 
 int /*<<< orphan*/  rc_hash ; 
 int /*<<< orphan*/  rc_lru ; 

__attribute__((used)) static void
nfsrc_freecache(struct nfsrvcache *rp)
{
	struct nfsrchash_bucket *hbp;

	LIST_REMOVE(rp, rc_hash);
	if (rp->rc_flag & RC_UDP) {
		TAILQ_REMOVE(&nfsrvudplru, rp, rc_lru);
		nfsrc_udpcachesize--;
	} else if (rp->rc_acked != RC_NO_SEQ) {
		hbp = NFSRCAHASH(rp->rc_sockref);
		mtx_lock(&hbp->mtx);
		if (rp->rc_acked == RC_NO_ACK)
			LIST_REMOVE(rp, rc_ahash);
		mtx_unlock(&hbp->mtx);
	}
	nfsrc_wanted(rp);
	if (rp->rc_flag & RC_REPMBUF) {
		mbuf_freem(rp->rc_reply);
		if (!(rp->rc_flag & RC_UDP))
			atomic_add_int(&nfsrc_tcpsavedreplies, -1);
	}
	free(rp, M_NFSRVCACHE);
	atomic_add_int(&nfsstatsv1.srvcache_size, -1);
}