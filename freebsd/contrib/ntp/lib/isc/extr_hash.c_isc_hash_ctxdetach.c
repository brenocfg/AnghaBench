#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  refcnt; } ;
typedef  TYPE_1__ isc_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int) ; 
 scalar_t__ VALID_HASH (TYPE_1__*) ; 
 int /*<<< orphan*/  destroy (TYPE_1__**) ; 
 int /*<<< orphan*/  isc_refcount_decrement (int /*<<< orphan*/ *,unsigned int*) ; 

void
isc_hash_ctxdetach(isc_hash_t **hctxp) {
	isc_hash_t *hctx;
	unsigned int refs;

	REQUIRE(hctxp != NULL && VALID_HASH(*hctxp));
	hctx = *hctxp;

	isc_refcount_decrement(&hctx->refcnt, &refs);
	if (refs == 0)
		destroy(&hctx);

	*hctxp = NULL;
}