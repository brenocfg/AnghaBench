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
typedef  int /*<<< orphan*/  u8 ;
struct crypto_tfm {int dummy; } ;
struct crypto_aes_ctx {int key_length; int /*<<< orphan*/  key_enc; } ;

/* Variables and functions */
 int /*<<< orphan*/  __aes_arm_encrypt (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 struct crypto_aes_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static void aes_arm_encrypt(struct crypto_tfm *tfm, u8 *out, const u8 *in)
{
	struct crypto_aes_ctx *ctx = crypto_tfm_ctx(tfm);
	int rounds = 6 + ctx->key_length / 4;

	__aes_arm_encrypt(ctx->key_enc, rounds, in, out);
}