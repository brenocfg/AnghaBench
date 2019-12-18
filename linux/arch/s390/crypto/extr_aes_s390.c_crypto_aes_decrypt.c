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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  cip; } ;
struct s390_aes_ctx {int fc; int /*<<< orphan*/  key; TYPE_1__ fallback; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 int CPACF_DECRYPT ; 
 int /*<<< orphan*/  cpacf_km (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_cipher_decrypt_one (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 struct s390_aes_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void crypto_aes_decrypt(struct crypto_tfm *tfm, u8 *out, const u8 *in)
{
	struct s390_aes_ctx *sctx = crypto_tfm_ctx(tfm);

	if (unlikely(!sctx->fc)) {
		crypto_cipher_decrypt_one(sctx->fallback.cip, out, in);
		return;
	}
	cpacf_km(sctx->fc | CPACF_DECRYPT,
		 &sctx->key, out, in, AES_BLOCK_SIZE);
}