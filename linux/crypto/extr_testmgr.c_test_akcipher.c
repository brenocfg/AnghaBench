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
struct crypto_akcipher {int dummy; } ;
struct akcipher_testvec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_akcipher_tfm (struct crypto_akcipher*) ; 
 char* crypto_tfm_alg_driver_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,char const*,int) ; 
 int test_akcipher_one (struct crypto_akcipher*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_akcipher(struct crypto_akcipher *tfm, const char *alg,
			 const struct akcipher_testvec *vecs,
			 unsigned int tcount)
{
	const char *algo =
		crypto_tfm_alg_driver_name(crypto_akcipher_tfm(tfm));
	int ret, i;

	for (i = 0; i < tcount; i++) {
		ret = test_akcipher_one(tfm, vecs++);
		if (!ret)
			continue;

		pr_err("alg: akcipher: test %d failed for %s, err=%d\n",
		       i + 1, algo, ret);
		return ret;
	}
	return 0;
}