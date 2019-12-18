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
struct testvec_config {int /*<<< orphan*/  name; } ;
struct hash_testvec {int /*<<< orphan*/  digest; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  TESTMGR_POISON_LEN ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testmgr_is_poison (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_hash_result(const char *type,
			     const u8 *result, unsigned int digestsize,
			     const struct hash_testvec *vec,
			     const char *vec_name,
			     const char *driver,
			     const struct testvec_config *cfg)
{
	if (memcmp(result, vec->digest, digestsize) != 0) {
		pr_err("alg: %s: %s test failed (wrong result) on test vector %s, cfg=\"%s\"\n",
		       type, driver, vec_name, cfg->name);
		return -EINVAL;
	}
	if (!testmgr_is_poison(&result[digestsize], TESTMGR_POISON_LEN)) {
		pr_err("alg: %s: %s overran result buffer on test vector %s, cfg=\"%s\"\n",
		       type, driver, vec_name, cfg->name);
		return -EOVERFLOW;
	}
	return 0;
}