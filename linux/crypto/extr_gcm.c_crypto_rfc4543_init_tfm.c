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
struct crypto_sync_skcipher {int dummy; } ;
struct crypto_rfc4543_req_ctx {int dummy; } ;
struct crypto_aead_spawn {int dummy; } ;
struct crypto_rfc4543_instance_ctx {struct crypto_aead_spawn aead; } ;
struct crypto_rfc4543_ctx {struct crypto_sync_skcipher* null; struct crypto_sync_skcipher* child; } ;
typedef  struct crypto_sync_skcipher crypto_aead ;
struct aead_instance {int dummy; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int /*<<< orphan*/ ,int) ; 
 scalar_t__ GCM_AES_IV_SIZE ; 
 scalar_t__ IS_ERR (struct crypto_sync_skcipher*) ; 
 int PTR_ERR (struct crypto_sync_skcipher*) ; 
 struct aead_instance* aead_alg_instance (struct crypto_sync_skcipher*) ; 
 struct crypto_rfc4543_instance_ctx* aead_instance_ctx (struct aead_instance*) ; 
 unsigned long crypto_aead_alignmask (struct crypto_sync_skcipher*) ; 
 struct crypto_rfc4543_ctx* crypto_aead_ctx (struct crypto_sync_skcipher*) ; 
 int /*<<< orphan*/  crypto_aead_reqsize (struct crypto_sync_skcipher*) ; 
 int /*<<< orphan*/  crypto_aead_set_reqsize (struct crypto_sync_skcipher*,scalar_t__) ; 
 int /*<<< orphan*/  crypto_free_aead (struct crypto_sync_skcipher*) ; 
 struct crypto_sync_skcipher* crypto_get_default_null_skcipher () ; 
 struct crypto_sync_skcipher* crypto_spawn_aead (struct crypto_aead_spawn*) ; 
 int crypto_tfm_ctx_alignment () ; 

__attribute__((used)) static int crypto_rfc4543_init_tfm(struct crypto_aead *tfm)
{
	struct aead_instance *inst = aead_alg_instance(tfm);
	struct crypto_rfc4543_instance_ctx *ictx = aead_instance_ctx(inst);
	struct crypto_aead_spawn *spawn = &ictx->aead;
	struct crypto_rfc4543_ctx *ctx = crypto_aead_ctx(tfm);
	struct crypto_aead *aead;
	struct crypto_sync_skcipher *null;
	unsigned long align;
	int err = 0;

	aead = crypto_spawn_aead(spawn);
	if (IS_ERR(aead))
		return PTR_ERR(aead);

	null = crypto_get_default_null_skcipher();
	err = PTR_ERR(null);
	if (IS_ERR(null))
		goto err_free_aead;

	ctx->child = aead;
	ctx->null = null;

	align = crypto_aead_alignmask(aead);
	align &= ~(crypto_tfm_ctx_alignment() - 1);
	crypto_aead_set_reqsize(
		tfm,
		sizeof(struct crypto_rfc4543_req_ctx) +
		ALIGN(crypto_aead_reqsize(aead), crypto_tfm_ctx_alignment()) +
		align + GCM_AES_IV_SIZE);

	return 0;

err_free_aead:
	crypto_free_aead(aead);
	return err;
}