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
struct crypto_akcipher {int dummy; } ;
struct TYPE_2__ {unsigned int n_sz; } ;
struct caam_rsa_ctx {TYPE_1__ key; } ;

/* Variables and functions */
 struct caam_rsa_ctx* akcipher_tfm_ctx (struct crypto_akcipher*) ; 

__attribute__((used)) static unsigned int caam_rsa_max_size(struct crypto_akcipher *tfm)
{
	struct caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);

	return ctx->key.n_sz;
}