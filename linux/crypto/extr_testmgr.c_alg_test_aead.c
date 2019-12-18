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
struct crypto_aead {int dummy; } ;
struct cipher_test_sglists {int dummy; } ;
struct aead_test_suite {scalar_t__ count; } ;
struct TYPE_2__ {struct aead_test_suite aead; } ;
struct alg_test_desc {TYPE_1__ suite; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECRYPT ; 
 int EINVAL ; 
 int /*<<< orphan*/  ENCRYPT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct crypto_aead*) ; 
 int PTR_ERR (struct crypto_aead*) ; 
 struct aead_request* aead_request_alloc (struct crypto_aead*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_free (struct aead_request*) ; 
 struct cipher_test_sglists* alloc_cipher_test_sglists () ; 
 struct crypto_aead* crypto_alloc_aead (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_aead (struct crypto_aead*) ; 
 int /*<<< orphan*/  free_cipher_test_sglists (struct cipher_test_sglists*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,...) ; 
 int test_aead (char const*,int /*<<< orphan*/ ,struct aead_test_suite const*,struct aead_request*,struct cipher_test_sglists*) ; 
 int test_aead_vs_generic_impl (char const*,struct alg_test_desc const*,struct aead_request*,struct cipher_test_sglists*) ; 

__attribute__((used)) static int alg_test_aead(const struct alg_test_desc *desc, const char *driver,
			 u32 type, u32 mask)
{
	const struct aead_test_suite *suite = &desc->suite.aead;
	struct crypto_aead *tfm;
	struct aead_request *req = NULL;
	struct cipher_test_sglists *tsgls = NULL;
	int err;

	if (suite->count <= 0) {
		pr_err("alg: aead: empty test suite for %s\n", driver);
		return -EINVAL;
	}

	tfm = crypto_alloc_aead(driver, type, mask);
	if (IS_ERR(tfm)) {
		pr_err("alg: aead: failed to allocate transform for %s: %ld\n",
		       driver, PTR_ERR(tfm));
		return PTR_ERR(tfm);
	}

	req = aead_request_alloc(tfm, GFP_KERNEL);
	if (!req) {
		pr_err("alg: aead: failed to allocate request for %s\n",
		       driver);
		err = -ENOMEM;
		goto out;
	}

	tsgls = alloc_cipher_test_sglists();
	if (!tsgls) {
		pr_err("alg: aead: failed to allocate test buffers for %s\n",
		       driver);
		err = -ENOMEM;
		goto out;
	}

	err = test_aead(driver, ENCRYPT, suite, req, tsgls);
	if (err)
		goto out;

	err = test_aead(driver, DECRYPT, suite, req, tsgls);
	if (err)
		goto out;

	err = test_aead_vs_generic_impl(driver, desc, req, tsgls);
out:
	free_cipher_test_sglists(tsgls);
	aead_request_free(req);
	crypto_free_aead(tfm);
	return err;
}