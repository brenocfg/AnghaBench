#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int aes_keylen; } ;
union fc_ctx_flags {int /*<<< orphan*/  f; TYPE_2__ w0; } ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {struct flexi_crypto_context* fctx; } ;
struct nitrox_crypto_ctx {TYPE_1__ u; } ;
struct TYPE_9__ {int /*<<< orphan*/  key; } ;
struct TYPE_10__ {TYPE_4__ u; } ;
struct TYPE_8__ {int /*<<< orphan*/  f; } ;
struct flexi_crypto_context {TYPE_5__ crypto; TYPE_3__ flags; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 struct nitrox_crypto_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_set_flags (struct crypto_aead*,int /*<<< orphan*/ ) ; 
 int flexi_aes_keylen (unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nitrox_aes_gcm_setkey(struct crypto_aead *aead, const u8 *key,
				 unsigned int keylen)
{
	int aes_keylen;
	struct nitrox_crypto_ctx *nctx = crypto_aead_ctx(aead);
	struct flexi_crypto_context *fctx;
	union fc_ctx_flags flags;

	aes_keylen = flexi_aes_keylen(keylen);
	if (aes_keylen < 0) {
		crypto_aead_set_flags(aead, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	/* fill crypto context */
	fctx = nctx->u.fctx;
	flags.f = be64_to_cpu(fctx->flags.f);
	flags.w0.aes_keylen = aes_keylen;
	fctx->flags.f = cpu_to_be64(flags.f);

	/* copy enc key to context */
	memset(&fctx->crypto, 0, sizeof(fctx->crypto));
	memcpy(fctx->crypto.u.key, key, keylen);

	return 0;
}