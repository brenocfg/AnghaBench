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
struct crypto_tfm {TYPE_1__* __crt_alg; } ;
struct TYPE_2__ {int /*<<< orphan*/  cra_ctxsize; } ;

/* Variables and functions */
 void* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  memzero_explicit (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mv_cesa_skcipher_cra_exit(struct crypto_tfm *tfm)
{
	void *ctx = crypto_tfm_ctx(tfm);

	memzero_explicit(ctx, tfm->__crt_alg->cra_ctxsize);
}