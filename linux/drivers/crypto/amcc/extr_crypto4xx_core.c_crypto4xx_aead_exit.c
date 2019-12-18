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
struct crypto_aead {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  aead; } ;
struct crypto4xx_ctx {TYPE_1__ sw_cipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto4xx_common_exit (struct crypto4xx_ctx*) ; 
 struct crypto4xx_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_free_aead (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void crypto4xx_aead_exit(struct crypto_aead *tfm)
{
	struct crypto4xx_ctx *ctx = crypto_aead_ctx(tfm);

	crypto4xx_common_exit(ctx);
	crypto_free_aead(ctx->sw_cipher.aead);
}