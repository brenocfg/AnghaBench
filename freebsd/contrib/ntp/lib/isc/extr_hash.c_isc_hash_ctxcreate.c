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
typedef  scalar_t__ isc_result_t ;
typedef  int /*<<< orphan*/  isc_mem_t ;
struct TYPE_6__ {unsigned int limit; size_t vectorlen; int /*<<< orphan*/  lock; int /*<<< orphan*/ * entropy; struct TYPE_6__* rndvector; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  initialized; int /*<<< orphan*/ * mctx; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ isc_hash_t ;
typedef  int /*<<< orphan*/  isc_entropy_t ;
typedef  TYPE_1__ hash_random_t ;
typedef  unsigned int hash_accum_t ;

/* Variables and functions */
 int /*<<< orphan*/  DESTROYLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HASH_MAGIC ; 
 int /*<<< orphan*/  ISC_FALSE ; 
 scalar_t__ ISC_R_NOMEMORY ; 
 scalar_t__ ISC_R_RANGE ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_entropy_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  isc_mem_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 TYPE_1__* isc_mem_get (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ *,TYPE_1__*,size_t) ; 
 scalar_t__ isc_mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ isc_refcount_init (int /*<<< orphan*/ *,int) ; 

isc_result_t
isc_hash_ctxcreate(isc_mem_t *mctx, isc_entropy_t *entropy,
		   unsigned int limit, isc_hash_t **hctxp)
{
	isc_result_t result;
	isc_hash_t *hctx;
	size_t vlen;
	hash_random_t *rv;
	hash_accum_t overflow_limit;

	REQUIRE(mctx != NULL);
	REQUIRE(hctxp != NULL && *hctxp == NULL);

	/*
	 * Overflow check.  Since our implementation only does a modulo
	 * operation at the last stage of hash calculation, the accumulator
	 * must not overflow.
	 */
	overflow_limit =
		1 << (((sizeof(hash_accum_t) - sizeof(hash_random_t))) * 8);
	if (overflow_limit < (limit + 1) * 0xff)
		return (ISC_R_RANGE);

	hctx = isc_mem_get(mctx, sizeof(isc_hash_t));
	if (hctx == NULL)
		return (ISC_R_NOMEMORY);

	vlen = sizeof(hash_random_t) * (limit + 1);
	rv = isc_mem_get(mctx, vlen);
	if (rv == NULL) {
		result = ISC_R_NOMEMORY;
		goto errout;
	}

	/*
	 * We need a lock.
	 */
	result = isc_mutex_init(&hctx->lock);
	if (result != ISC_R_SUCCESS)
		goto errout;

	/*
	 * From here down, no failures will/can occur.
	 */
	hctx->magic = HASH_MAGIC;
	hctx->mctx = NULL;
	isc_mem_attach(mctx, &hctx->mctx);
	hctx->initialized = ISC_FALSE;
	result = isc_refcount_init(&hctx->refcnt, 1);
	if (result != ISC_R_SUCCESS)
		goto cleanup_lock;
	hctx->entropy = NULL;
	hctx->limit = limit;
	hctx->vectorlen = vlen;
	hctx->rndvector = rv;

#ifdef BIND9
	if (entropy != NULL)
		isc_entropy_attach(entropy, &hctx->entropy);
#else
	UNUSED(entropy);
#endif

	*hctxp = hctx;
	return (ISC_R_SUCCESS);

 cleanup_lock:
	DESTROYLOCK(&hctx->lock);
 errout:
	isc_mem_put(mctx, hctx, sizeof(isc_hash_t));
	if (rv != NULL)
		isc_mem_put(mctx, rv, vlen);

	return (result);
}