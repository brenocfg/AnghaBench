#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_mem_t ;
struct TYPE_6__ {int vectorlen; int /*<<< orphan*/  lock; struct TYPE_6__* rndvector; int /*<<< orphan*/ * entropy; int /*<<< orphan*/ * mctx; int /*<<< orphan*/  refcnt; } ;
typedef  TYPE_1__ isc_hash_t ;
typedef  int /*<<< orphan*/  canary1 ;
typedef  int /*<<< orphan*/  canary0 ;

/* Variables and functions */
 int /*<<< orphan*/  DESTROYLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_entropy_detach (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  isc_mem_detach (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  isc_refcount_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
destroy(isc_hash_t **hctxp) {
	isc_hash_t *hctx;
	isc_mem_t *mctx;
	unsigned char canary0[4], canary1[4];

	REQUIRE(hctxp != NULL && *hctxp != NULL);
	hctx = *hctxp;
	*hctxp = NULL;

	LOCK(&hctx->lock);

	isc_refcount_destroy(&hctx->refcnt);

	mctx = hctx->mctx;
#ifdef BIND9
	if (hctx->entropy != NULL)
		isc_entropy_detach(&hctx->entropy);
#endif
	if (hctx->rndvector != NULL)
		isc_mem_put(mctx, hctx->rndvector, hctx->vectorlen);

	UNLOCK(&hctx->lock);

	DESTROYLOCK(&hctx->lock);

	memcpy(canary0, hctx + 1, sizeof(canary0));
	memset(hctx, 0, sizeof(isc_hash_t));
	memcpy(canary1, hctx + 1, sizeof(canary1));
	INSIST(memcmp(canary0, canary1, sizeof(canary0)) == 0);
	isc_mem_put(mctx, hctx, sizeof(isc_hash_t));
	isc_mem_detach(&mctx);
}