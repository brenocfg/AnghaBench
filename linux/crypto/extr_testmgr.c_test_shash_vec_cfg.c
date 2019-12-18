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
struct testvec_config {int name; scalar_t__ finalization_type; scalar_t__ nosimd; } ;
struct test_sglist {int nents; TYPE_1__* sgl; } ;
struct test_sg_division {scalar_t__ flush_type; scalar_t__ nosimd; } ;
struct shash_desc {int /*<<< orphan*/ * __ctx; struct crypto_shash* tfm; } ;
struct hash_testvec {int setkey_error; int digest_error; int /*<<< orphan*/  ksize; int /*<<< orphan*/  key; } ;
struct crypto_shash {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOVERFLOW ; 
 scalar_t__ FINALIZATION_TYPE_DIGEST ; 
 scalar_t__ FINALIZATION_TYPE_FINUP ; 
 scalar_t__ FLUSH_TYPE_REIMPORT ; 
 int HASH_MAX_DIGESTSIZE ; 
 int TESTMGR_POISON_LEN ; 
 int XBUFSIZE ; 
 int build_hash_sglist (struct test_sglist*,struct hash_testvec const*,struct testvec_config const*,unsigned int const,struct test_sg_division const**) ; 
 int check_hash_result (char*,int /*<<< orphan*/ *,unsigned int const,struct hash_testvec const*,char const*,char const*,struct testvec_config const*) ; 
 int check_shash_op (char*,int,char const*,char const*,struct testvec_config const*) ; 
 int /*<<< orphan*/  crypto_disable_simd_for_test () ; 
 int /*<<< orphan*/  crypto_reenable_simd_for_test () ; 
 unsigned int crypto_shash_alignmask (struct crypto_shash*) ; 
 int crypto_shash_descsize (struct crypto_shash*) ; 
 int crypto_shash_digest (struct shash_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int crypto_shash_digestsize (struct crypto_shash*) ; 
 int crypto_shash_export (struct shash_desc*,int /*<<< orphan*/ *) ; 
 int crypto_shash_final (struct shash_desc*,int /*<<< orphan*/ *) ; 
 int crypto_shash_finup (struct shash_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_shash_get_flags (struct crypto_shash*) ; 
 int crypto_shash_import (struct shash_desc*,int /*<<< orphan*/ *) ; 
 int crypto_shash_init (struct shash_desc*) ; 
 int crypto_shash_setkey (struct crypto_shash*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int crypto_shash_statesize (struct crypto_shash*) ; 
 int crypto_shash_update (struct shash_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,char const*,int,...) ; 
 int /*<<< orphan*/  sg_data (TYPE_1__*) ; 
 int /*<<< orphan*/  testmgr_is_poison (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  testmgr_poison (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int test_shash_vec_cfg(const char *driver,
			      const struct hash_testvec *vec,
			      const char *vec_name,
			      const struct testvec_config *cfg,
			      struct shash_desc *desc,
			      struct test_sglist *tsgl,
			      u8 *hashstate)
{
	struct crypto_shash *tfm = desc->tfm;
	const unsigned int alignmask = crypto_shash_alignmask(tfm);
	const unsigned int digestsize = crypto_shash_digestsize(tfm);
	const unsigned int statesize = crypto_shash_statesize(tfm);
	const struct test_sg_division *divs[XBUFSIZE];
	unsigned int i;
	u8 result[HASH_MAX_DIGESTSIZE + TESTMGR_POISON_LEN];
	int err;

	/* Set the key, if specified */
	if (vec->ksize) {
		err = crypto_shash_setkey(tfm, vec->key, vec->ksize);
		if (err) {
			if (err == vec->setkey_error)
				return 0;
			pr_err("alg: shash: %s setkey failed on test vector %s; expected_error=%d, actual_error=%d, flags=%#x\n",
			       driver, vec_name, vec->setkey_error, err,
			       crypto_shash_get_flags(tfm));
			return err;
		}
		if (vec->setkey_error) {
			pr_err("alg: shash: %s setkey unexpectedly succeeded on test vector %s; expected_error=%d\n",
			       driver, vec_name, vec->setkey_error);
			return -EINVAL;
		}
	}

	/* Build the scatterlist for the source data */
	err = build_hash_sglist(tsgl, vec, cfg, alignmask, divs);
	if (err) {
		pr_err("alg: shash: %s: error preparing scatterlist for test vector %s, cfg=\"%s\"\n",
		       driver, vec_name, cfg->name);
		return err;
	}

	/* Do the actual hashing */

	testmgr_poison(desc->__ctx, crypto_shash_descsize(tfm));
	testmgr_poison(result, digestsize + TESTMGR_POISON_LEN);

	if (cfg->finalization_type == FINALIZATION_TYPE_DIGEST ||
	    vec->digest_error) {
		/* Just using digest() */
		if (tsgl->nents != 1)
			return 0;
		if (cfg->nosimd)
			crypto_disable_simd_for_test();
		err = crypto_shash_digest(desc, sg_data(&tsgl->sgl[0]),
					  tsgl->sgl[0].length, result);
		if (cfg->nosimd)
			crypto_reenable_simd_for_test();
		if (err) {
			if (err == vec->digest_error)
				return 0;
			pr_err("alg: shash: %s digest() failed on test vector %s; expected_error=%d, actual_error=%d, cfg=\"%s\"\n",
			       driver, vec_name, vec->digest_error, err,
			       cfg->name);
			return err;
		}
		if (vec->digest_error) {
			pr_err("alg: shash: %s digest() unexpectedly succeeded on test vector %s; expected_error=%d, cfg=\"%s\"\n",
			       driver, vec_name, vec->digest_error, cfg->name);
			return -EINVAL;
		}
		goto result_ready;
	}

	/* Using init(), zero or more update(), then final() or finup() */

	if (cfg->nosimd)
		crypto_disable_simd_for_test();
	err = crypto_shash_init(desc);
	if (cfg->nosimd)
		crypto_reenable_simd_for_test();
	err = check_shash_op("init", err, driver, vec_name, cfg);
	if (err)
		return err;

	for (i = 0; i < tsgl->nents; i++) {
		if (i + 1 == tsgl->nents &&
		    cfg->finalization_type == FINALIZATION_TYPE_FINUP) {
			if (divs[i]->nosimd)
				crypto_disable_simd_for_test();
			err = crypto_shash_finup(desc, sg_data(&tsgl->sgl[i]),
						 tsgl->sgl[i].length, result);
			if (divs[i]->nosimd)
				crypto_reenable_simd_for_test();
			err = check_shash_op("finup", err, driver, vec_name,
					     cfg);
			if (err)
				return err;
			goto result_ready;
		}
		if (divs[i]->nosimd)
			crypto_disable_simd_for_test();
		err = crypto_shash_update(desc, sg_data(&tsgl->sgl[i]),
					  tsgl->sgl[i].length);
		if (divs[i]->nosimd)
			crypto_reenable_simd_for_test();
		err = check_shash_op("update", err, driver, vec_name, cfg);
		if (err)
			return err;
		if (divs[i]->flush_type == FLUSH_TYPE_REIMPORT) {
			/* Test ->export() and ->import() */
			testmgr_poison(hashstate + statesize,
				       TESTMGR_POISON_LEN);
			err = crypto_shash_export(desc, hashstate);
			err = check_shash_op("export", err, driver, vec_name,
					     cfg);
			if (err)
				return err;
			if (!testmgr_is_poison(hashstate + statesize,
					       TESTMGR_POISON_LEN)) {
				pr_err("alg: shash: %s export() overran state buffer on test vector %s, cfg=\"%s\"\n",
				       driver, vec_name, cfg->name);
				return -EOVERFLOW;
			}
			testmgr_poison(desc->__ctx, crypto_shash_descsize(tfm));
			err = crypto_shash_import(desc, hashstate);
			err = check_shash_op("import", err, driver, vec_name,
					     cfg);
			if (err)
				return err;
		}
	}

	if (cfg->nosimd)
		crypto_disable_simd_for_test();
	err = crypto_shash_final(desc, result);
	if (cfg->nosimd)
		crypto_reenable_simd_for_test();
	err = check_shash_op("final", err, driver, vec_name, cfg);
	if (err)
		return err;
result_ready:
	return check_hash_result("shash", result, digestsize, vec, vec_name,
				 driver, cfg);
}