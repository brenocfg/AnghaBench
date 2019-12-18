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
typedef  int /*<<< orphan*/  u32 ;
struct crypto_kpp {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  count; int /*<<< orphan*/  vecs; } ;
struct TYPE_4__ {TYPE_1__ kpp; } ;
struct alg_test_desc {TYPE_2__ suite; int /*<<< orphan*/  alg; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_kpp*) ; 
 int PTR_ERR (struct crypto_kpp*) ; 
 struct crypto_kpp* crypto_alloc_kpp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_kpp (struct crypto_kpp*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,int) ; 
 int test_kpp (struct crypto_kpp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alg_test_kpp(const struct alg_test_desc *desc, const char *driver,
			u32 type, u32 mask)
{
	struct crypto_kpp *tfm;
	int err = 0;

	tfm = crypto_alloc_kpp(driver, type, mask);
	if (IS_ERR(tfm)) {
		pr_err("alg: kpp: Failed to load tfm for %s: %ld\n",
		       driver, PTR_ERR(tfm));
		return PTR_ERR(tfm);
	}
	if (desc->suite.kpp.vecs)
		err = test_kpp(tfm, desc->alg, desc->suite.kpp.vecs,
			       desc->suite.kpp.count);

	crypto_free_kpp(tfm);
	return err;
}