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
struct padlock_sha_ctx {void* psc_buf; int /*<<< orphan*/  psc_size; int /*<<< orphan*/  psc_offset; } ;
struct auth_hash {scalar_t__ type; int /*<<< orphan*/  ctxsize; } ;

/* Variables and functions */
 scalar_t__ CRYPTO_SHA1_HMAC ; 
 scalar_t__ CRYPTO_SHA2_256_HMAC ; 
 int /*<<< orphan*/  M_PADLOCK ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int VIA_HAS_SHA ; 
 int /*<<< orphan*/  bcopy (void*,void*,int /*<<< orphan*/ ) ; 
 void* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int via_feature_xcrypt ; 

__attribute__((used)) static void
padlock_copy_ctx(struct auth_hash *axf, void *sctx, void *dctx)
{

	if ((via_feature_xcrypt & VIA_HAS_SHA) != 0 &&
	    (axf->type == CRYPTO_SHA1_HMAC ||
	     axf->type == CRYPTO_SHA2_256_HMAC)) {
		struct padlock_sha_ctx *spctx = sctx, *dpctx = dctx;

		dpctx->psc_offset = spctx->psc_offset;
		dpctx->psc_size = spctx->psc_size;
		dpctx->psc_buf = malloc(dpctx->psc_size, M_PADLOCK, M_WAITOK);
		bcopy(spctx->psc_buf, dpctx->psc_buf, dpctx->psc_size);
	} else {
		bcopy(sctx, dctx, axf->ctxsize);
	}
}