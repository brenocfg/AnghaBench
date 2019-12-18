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
struct crypto_ahash {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct crypto_ahash*) ; 
 int PTR_ERR (struct crypto_ahash*) ; 
 struct ahash_request* ahash_request_alloc (struct crypto_ahash*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahash_request_free (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_ahash_clear_flags (struct crypto_ahash*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_tfm (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_alloc_ahash (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_ahash (struct crypto_ahash*) ; 
 unsigned int crypto_tfm_alg_blocksize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kcalloc (int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int mv_cesa_ahmac_iv_state_init (struct ahash_request*,int /*<<< orphan*/ *,void*,unsigned int) ; 
 int mv_cesa_ahmac_pad_init (struct ahash_request*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int mv_cesa_ahmac_setkey(const char *hash_alg_name,
				const u8 *key, unsigned int keylen,
				void *istate, void *ostate)
{
	struct ahash_request *req;
	struct crypto_ahash *tfm;
	unsigned int blocksize;
	u8 *ipad = NULL;
	u8 *opad;
	int ret;

	tfm = crypto_alloc_ahash(hash_alg_name, 0, 0);
	if (IS_ERR(tfm))
		return PTR_ERR(tfm);

	req = ahash_request_alloc(tfm, GFP_KERNEL);
	if (!req) {
		ret = -ENOMEM;
		goto free_ahash;
	}

	crypto_ahash_clear_flags(tfm, ~0);

	blocksize = crypto_tfm_alg_blocksize(crypto_ahash_tfm(tfm));

	ipad = kcalloc(2, blocksize, GFP_KERNEL);
	if (!ipad) {
		ret = -ENOMEM;
		goto free_req;
	}

	opad = ipad + blocksize;

	ret = mv_cesa_ahmac_pad_init(req, key, keylen, ipad, opad, blocksize);
	if (ret)
		goto free_ipad;

	ret = mv_cesa_ahmac_iv_state_init(req, ipad, istate, blocksize);
	if (ret)
		goto free_ipad;

	ret = mv_cesa_ahmac_iv_state_init(req, opad, ostate, blocksize);

free_ipad:
	kfree(ipad);
free_req:
	ahash_request_free(req);
free_ahash:
	crypto_free_ahash(tfm);

	return ret;
}