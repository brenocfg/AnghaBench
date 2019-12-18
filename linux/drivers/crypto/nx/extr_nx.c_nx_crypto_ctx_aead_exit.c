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
struct nx_crypto_ctx {int /*<<< orphan*/  kmem; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 struct nx_crypto_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ ) ; 

void nx_crypto_ctx_aead_exit(struct crypto_aead *tfm)
{
	struct nx_crypto_ctx *nx_ctx = crypto_aead_ctx(tfm);

	kzfree(nx_ctx->kmem);
}