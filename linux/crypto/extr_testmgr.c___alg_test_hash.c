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
struct test_sglist {int dummy; } ;
typedef  struct test_sglist u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  struct test_sglist shash_desc ;
struct hash_testvec {int dummy; } ;
struct crypto_shash {int dummy; } ;
struct crypto_ahash {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct crypto_ahash*) ; 
 int PTR_ERR (struct crypto_ahash*) ; 
 unsigned int TESTMGR_POISON_LEN ; 
 struct ahash_request* ahash_request_alloc (struct crypto_ahash*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahash_request_free (struct ahash_request*) ; 
 int alloc_shash (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct crypto_shash**,struct test_sglist**) ; 
 int /*<<< orphan*/  cond_resched () ; 
 unsigned int crypto_ahash_statesize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_alloc_ahash (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_ahash (struct crypto_ahash*) ; 
 int /*<<< orphan*/  crypto_free_shash (struct crypto_shash*) ; 
 int /*<<< orphan*/  crypto_shash_statesize (struct crypto_shash*) ; 
 int /*<<< orphan*/  destroy_test_sglist (struct test_sglist*) ; 
 scalar_t__ init_test_sglist (struct test_sglist*) ; 
 int /*<<< orphan*/  kfree (struct test_sglist*) ; 
 struct test_sglist* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int max (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,...) ; 
 int test_hash_vec (char const*,struct hash_testvec const*,unsigned int,struct ahash_request*,struct test_sglist*,struct test_sglist*,struct test_sglist*) ; 
 int test_hash_vs_generic_impl (char const*,char const*,unsigned int,struct ahash_request*,struct test_sglist*,struct test_sglist*,struct test_sglist*) ; 

__attribute__((used)) static int __alg_test_hash(const struct hash_testvec *vecs,
			   unsigned int num_vecs, const char *driver,
			   u32 type, u32 mask,
			   const char *generic_driver, unsigned int maxkeysize)
{
	struct crypto_ahash *atfm = NULL;
	struct ahash_request *req = NULL;
	struct crypto_shash *stfm = NULL;
	struct shash_desc *desc = NULL;
	struct test_sglist *tsgl = NULL;
	u8 *hashstate = NULL;
	unsigned int statesize;
	unsigned int i;
	int err;

	/*
	 * Always test the ahash API.  This works regardless of whether the
	 * algorithm is implemented as ahash or shash.
	 */

	atfm = crypto_alloc_ahash(driver, type, mask);
	if (IS_ERR(atfm)) {
		pr_err("alg: hash: failed to allocate transform for %s: %ld\n",
		       driver, PTR_ERR(atfm));
		return PTR_ERR(atfm);
	}

	req = ahash_request_alloc(atfm, GFP_KERNEL);
	if (!req) {
		pr_err("alg: hash: failed to allocate request for %s\n",
		       driver);
		err = -ENOMEM;
		goto out;
	}

	/*
	 * If available also test the shash API, to cover corner cases that may
	 * be missed by testing the ahash API only.
	 */
	err = alloc_shash(driver, type, mask, &stfm, &desc);
	if (err)
		goto out;

	tsgl = kmalloc(sizeof(*tsgl), GFP_KERNEL);
	if (!tsgl || init_test_sglist(tsgl) != 0) {
		pr_err("alg: hash: failed to allocate test buffers for %s\n",
		       driver);
		kfree(tsgl);
		tsgl = NULL;
		err = -ENOMEM;
		goto out;
	}

	statesize = crypto_ahash_statesize(atfm);
	if (stfm)
		statesize = max(statesize, crypto_shash_statesize(stfm));
	hashstate = kmalloc(statesize + TESTMGR_POISON_LEN, GFP_KERNEL);
	if (!hashstate) {
		pr_err("alg: hash: failed to allocate hash state buffer for %s\n",
		       driver);
		err = -ENOMEM;
		goto out;
	}

	for (i = 0; i < num_vecs; i++) {
		err = test_hash_vec(driver, &vecs[i], i, req, desc, tsgl,
				    hashstate);
		if (err)
			goto out;
		cond_resched();
	}
	err = test_hash_vs_generic_impl(driver, generic_driver, maxkeysize, req,
					desc, tsgl, hashstate);
out:
	kfree(hashstate);
	if (tsgl) {
		destroy_test_sglist(tsgl);
		kfree(tsgl);
	}
	kfree(desc);
	crypto_free_shash(stfm);
	ahash_request_free(req);
	crypto_free_ahash(atfm);
	return err;
}