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
struct simd_aead_ctx {int /*<<< orphan*/  cryptd_tfm; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cryptd_free_aead (int /*<<< orphan*/ ) ; 
 struct simd_aead_ctx* crypto_aead_ctx (struct crypto_aead*) ; 

__attribute__((used)) static void simd_aead_exit(struct crypto_aead *tfm)
{
	struct simd_aead_ctx *ctx = crypto_aead_ctx(tfm);

	cryptd_free_aead(ctx->cryptd_tfm);
}