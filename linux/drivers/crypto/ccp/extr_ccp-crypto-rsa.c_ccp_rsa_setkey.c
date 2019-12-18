#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rsa_key {int /*<<< orphan*/  d_sz; int /*<<< orphan*/  d; int /*<<< orphan*/  e_sz; int /*<<< orphan*/  e; int /*<<< orphan*/  n_sz; int /*<<< orphan*/  n; } ;
struct crypto_akcipher {int dummy; } ;
struct TYPE_3__ {int n_len; int key_len; int e_len; int d_len; int /*<<< orphan*/  d_buf; int /*<<< orphan*/  d_sg; int /*<<< orphan*/  e_buf; int /*<<< orphan*/  e_sg; int /*<<< orphan*/  n_buf; int /*<<< orphan*/  n_sg; } ;
struct TYPE_4__ {TYPE_1__ rsa; } ;
struct ccp_ctx {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  raw_key ;

/* Variables and functions */
 int EINVAL ; 
 struct ccp_ctx* akcipher_tfm_ctx (struct crypto_akcipher*) ; 
 scalar_t__ ccp_check_key_length (int) ; 
 int ccp_copy_and_save_keypart (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccp_rsa_free_key_bufs (struct ccp_ctx*) ; 
 int /*<<< orphan*/  memset (struct rsa_key*,int /*<<< orphan*/ ,int) ; 
 int rsa_parse_priv_key (struct rsa_key*,void const*,unsigned int) ; 
 int rsa_parse_pub_key (struct rsa_key*,void const*,unsigned int) ; 
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ccp_rsa_setkey(struct crypto_akcipher *tfm, const void *key,
			  unsigned int keylen, bool private)
{
	struct ccp_ctx *ctx = akcipher_tfm_ctx(tfm);
	struct rsa_key raw_key;
	int ret;

	ccp_rsa_free_key_bufs(ctx);
	memset(&raw_key, 0, sizeof(raw_key));

	/* Code borrowed from crypto/rsa.c */
	if (private)
		ret = rsa_parse_priv_key(&raw_key, key, keylen);
	else
		ret = rsa_parse_pub_key(&raw_key, key, keylen);
	if (ret)
		goto n_key;

	ret = ccp_copy_and_save_keypart(&ctx->u.rsa.n_buf, &ctx->u.rsa.n_len,
					raw_key.n, raw_key.n_sz);
	if (ret)
		goto key_err;
	sg_init_one(&ctx->u.rsa.n_sg, ctx->u.rsa.n_buf, ctx->u.rsa.n_len);

	ctx->u.rsa.key_len = ctx->u.rsa.n_len << 3; /* convert to bits */
	if (ccp_check_key_length(ctx->u.rsa.key_len)) {
		ret = -EINVAL;
		goto key_err;
	}

	ret = ccp_copy_and_save_keypart(&ctx->u.rsa.e_buf, &ctx->u.rsa.e_len,
					raw_key.e, raw_key.e_sz);
	if (ret)
		goto key_err;
	sg_init_one(&ctx->u.rsa.e_sg, ctx->u.rsa.e_buf, ctx->u.rsa.e_len);

	if (private) {
		ret = ccp_copy_and_save_keypart(&ctx->u.rsa.d_buf,
						&ctx->u.rsa.d_len,
						raw_key.d, raw_key.d_sz);
		if (ret)
			goto key_err;
		sg_init_one(&ctx->u.rsa.d_sg,
			    ctx->u.rsa.d_buf, ctx->u.rsa.d_len);
	}

	return 0;

key_err:
	ccp_rsa_free_key_bufs(ctx);

n_key:
	return ret;
}