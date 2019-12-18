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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int ndigits; } ;
struct ecrdsa_ctx {TYPE_1__ pub_key; } ;
struct crypto_akcipher {int dummy; } ;

/* Variables and functions */
 struct ecrdsa_ctx* akcipher_tfm_ctx (struct crypto_akcipher*) ; 

__attribute__((used)) static unsigned int ecrdsa_max_size(struct crypto_akcipher *tfm)
{
	struct ecrdsa_ctx *ctx = akcipher_tfm_ctx(tfm);

	/*
	 * Verify doesn't need any output, so it's just informational
	 * for keyctl to determine the key bit size.
	 */
	return ctx->pub_key.ndigits * sizeof(u64);
}