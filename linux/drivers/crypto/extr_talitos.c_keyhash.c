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
struct talitos_ctx {scalar_t__ keylen; } ;
struct scatterlist {int dummy; } ;
struct crypto_wait {int dummy; } ;
struct crypto_ahash {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ahash_request* ahash_request_alloc (struct crypto_ahash*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahash_request_free (struct ahash_request*) ; 
 int /*<<< orphan*/  ahash_request_set_callback (struct ahash_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct crypto_wait*) ; 
 int /*<<< orphan*/  ahash_request_set_crypt (struct ahash_request*,struct scatterlist*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  crypto_ahash_digest (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_ahash_tfm (struct crypto_ahash*) ; 
 int /*<<< orphan*/  crypto_init_wait (struct crypto_wait*) ; 
 int /*<<< orphan*/  crypto_req_done ; 
 struct talitos_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int crypto_wait_req (int /*<<< orphan*/ ,struct crypto_wait*) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int keyhash(struct crypto_ahash *tfm, const u8 *key, unsigned int keylen,
		   u8 *hash)
{
	struct talitos_ctx *ctx = crypto_tfm_ctx(crypto_ahash_tfm(tfm));

	struct scatterlist sg[1];
	struct ahash_request *req;
	struct crypto_wait wait;
	int ret;

	crypto_init_wait(&wait);

	req = ahash_request_alloc(tfm, GFP_KERNEL);
	if (!req)
		return -ENOMEM;

	/* Keep tfm keylen == 0 during hash of the long key */
	ctx->keylen = 0;
	ahash_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				   crypto_req_done, &wait);

	sg_init_one(&sg[0], key, keylen);

	ahash_request_set_crypt(req, sg, hash, keylen);
	ret = crypto_wait_req(crypto_ahash_digest(req), &wait);

	ahash_request_free(req);

	return ret;
}