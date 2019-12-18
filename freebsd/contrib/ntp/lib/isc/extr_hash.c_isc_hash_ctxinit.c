#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pr ;
typedef  int /*<<< orphan*/  isc_uint32_t ;
typedef  scalar_t__ isc_result_t ;
struct TYPE_3__ {scalar_t__ initialized; unsigned int vectorlen; int /*<<< orphan*/  lock; scalar_t__ rndvector; scalar_t__ entropy; } ;
typedef  TYPE_1__ isc_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int) ; 
 scalar_t__ ISC_R_SUCCESS ; 
 scalar_t__ ISC_TRUE ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ isc_entropy_getdata (scalar_t__,scalar_t__,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_random_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,unsigned int) ; 

void
isc_hash_ctxinit(isc_hash_t *hctx) {
	LOCK(&hctx->lock);

	if (hctx->initialized == ISC_TRUE)
		goto out;

	if (hctx->entropy) {
#ifdef BIND9
		isc_result_t result;

		result = isc_entropy_getdata(hctx->entropy,
					     hctx->rndvector, hctx->vectorlen,
					     NULL, 0);
		INSIST(result == ISC_R_SUCCESS);
#else
		INSIST(0);
#endif
	} else {
		isc_uint32_t pr;
		unsigned int i, copylen;
		unsigned char *p;

		p = (unsigned char *)hctx->rndvector;
		for (i = 0; i < hctx->vectorlen; i += copylen, p += copylen) {
			isc_random_get(&pr);
			if (i + sizeof(pr) <= hctx->vectorlen)
				copylen = sizeof(pr);
			else
				copylen = hctx->vectorlen - i;

			memcpy(p, &pr, copylen);
		}
		INSIST(p == (unsigned char *)hctx->rndvector +
		       hctx->vectorlen);
	}

	hctx->initialized = ISC_TRUE;

 out:
	UNLOCK(&hctx->lock);
}