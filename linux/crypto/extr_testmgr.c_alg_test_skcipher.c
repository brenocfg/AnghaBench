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
typedef  int /*<<< orphan*/  u32 ;
struct skcipher_request {int dummy; } ;
struct crypto_skcipher {int dummy; } ;
struct cipher_test_suite {scalar_t__ count; } ;
struct cipher_test_sglists {int dummy; } ;
struct TYPE_2__ {struct cipher_test_suite cipher; } ;
struct alg_test_desc {int /*<<< orphan*/  generic_driver; TYPE_1__ suite; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECRYPT ; 
 int EINVAL ; 
 int /*<<< orphan*/  ENCRYPT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct crypto_skcipher*) ; 
 int PTR_ERR (struct crypto_skcipher*) ; 
 struct cipher_test_sglists* alloc_cipher_test_sglists () ; 
 struct crypto_skcipher* crypto_alloc_skcipher (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_skcipher (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  free_cipher_test_sglists (struct cipher_test_sglists*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,...) ; 
 struct skcipher_request* skcipher_request_alloc (struct crypto_skcipher*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_free (struct skcipher_request*) ; 
 int test_skcipher (char const*,int /*<<< orphan*/ ,struct cipher_test_suite const*,struct skcipher_request*,struct cipher_test_sglists*) ; 
 int test_skcipher_vs_generic_impl (char const*,int /*<<< orphan*/ ,struct skcipher_request*,struct cipher_test_sglists*) ; 

__attribute__((used)) static int alg_test_skcipher(const struct alg_test_desc *desc,
			     const char *driver, u32 type, u32 mask)
{
	const struct cipher_test_suite *suite = &desc->suite.cipher;
	struct crypto_skcipher *tfm;
	struct skcipher_request *req = NULL;
	struct cipher_test_sglists *tsgls = NULL;
	int err;

	if (suite->count <= 0) {
		pr_err("alg: skcipher: empty test suite for %s\n", driver);
		return -EINVAL;
	}

	tfm = crypto_alloc_skcipher(driver, type, mask);
	if (IS_ERR(tfm)) {
		pr_err("alg: skcipher: failed to allocate transform for %s: %ld\n",
		       driver, PTR_ERR(tfm));
		return PTR_ERR(tfm);
	}

	req = skcipher_request_alloc(tfm, GFP_KERNEL);
	if (!req) {
		pr_err("alg: skcipher: failed to allocate request for %s\n",
		       driver);
		err = -ENOMEM;
		goto out;
	}

	tsgls = alloc_cipher_test_sglists();
	if (!tsgls) {
		pr_err("alg: skcipher: failed to allocate test buffers for %s\n",
		       driver);
		err = -ENOMEM;
		goto out;
	}

	err = test_skcipher(driver, ENCRYPT, suite, req, tsgls);
	if (err)
		goto out;

	err = test_skcipher(driver, DECRYPT, suite, req, tsgls);
	if (err)
		goto out;

	err = test_skcipher_vs_generic_impl(driver, desc->generic_driver, req,
					    tsgls);
out:
	free_cipher_test_sglists(tsgls);
	skcipher_request_free(req);
	crypto_free_skcipher(tfm);
	return err;
}