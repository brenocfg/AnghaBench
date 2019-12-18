#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ixp_ctx {int /*<<< orphan*/  completion; int /*<<< orphan*/  configuring; int /*<<< orphan*/  authkey_len; int /*<<< orphan*/  authkey; int /*<<< orphan*/  enckey_len; int /*<<< orphan*/  enckey; int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; } ;
struct TYPE_3__ {int crt_flags; } ;
struct crypto_aead {TYPE_1__ base; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_FORBID_WEAK_KEYS ; 
 int CRYPTO_TFM_RES_WEAK_KEY ; 
 int EINVAL ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct ixp_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 unsigned int crypto_aead_maxauthsize (struct crypto_aead*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_sa_dir (int /*<<< orphan*/ *) ; 
 int setup_auth (TYPE_1__*,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int setup_cipher (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aead_setup(struct crypto_aead *tfm, unsigned int authsize)
{
	struct ixp_ctx *ctx = crypto_aead_ctx(tfm);
	u32 *flags = &tfm->base.crt_flags;
	unsigned digest_len = crypto_aead_maxauthsize(tfm);
	int ret;

	if (!ctx->enckey_len && !ctx->authkey_len)
		return 0;
	init_completion(&ctx->completion);
	atomic_inc(&ctx->configuring);

	reset_sa_dir(&ctx->encrypt);
	reset_sa_dir(&ctx->decrypt);

	ret = setup_cipher(&tfm->base, 0, ctx->enckey, ctx->enckey_len);
	if (ret)
		goto out;
	ret = setup_cipher(&tfm->base, 1, ctx->enckey, ctx->enckey_len);
	if (ret)
		goto out;
	ret = setup_auth(&tfm->base, 0, authsize, ctx->authkey,
			ctx->authkey_len, digest_len);
	if (ret)
		goto out;
	ret = setup_auth(&tfm->base, 1, authsize,  ctx->authkey,
			ctx->authkey_len, digest_len);
	if (ret)
		goto out;

	if (*flags & CRYPTO_TFM_RES_WEAK_KEY) {
		if (*flags & CRYPTO_TFM_REQ_FORBID_WEAK_KEYS) {
			ret = -EINVAL;
			goto out;
		} else {
			*flags &= ~CRYPTO_TFM_RES_WEAK_KEY;
		}
	}
out:
	if (!atomic_dec_and_test(&ctx->configuring))
		wait_for_completion(&ctx->completion);
	return ret;
}