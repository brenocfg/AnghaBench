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
struct testvec_config {int dummy; } ;
struct test_sglist {int dummy; } ;
struct shash_desc {int dummy; } ;
struct hash_testvec {int dummy; } ;
struct ahash_request {int dummy; } ;
typedef  int /*<<< orphan*/  cfgname ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct testvec_config*) ; 
 int TESTVEC_CONFIG_NAMELEN ; 
 int /*<<< orphan*/  cond_resched () ; 
 struct testvec_config* default_hash_testvec_configs ; 
 unsigned int fuzz_iterations ; 
 int /*<<< orphan*/  generate_random_testvec_config (struct testvec_config*,char*,int) ; 
 int /*<<< orphan*/  noextratests ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 int test_hash_vec_cfg (char const*,struct hash_testvec const*,char*,struct testvec_config*,struct ahash_request*,struct shash_desc*,struct test_sglist*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_hash_vec(const char *driver, const struct hash_testvec *vec,
			 unsigned int vec_num, struct ahash_request *req,
			 struct shash_desc *desc, struct test_sglist *tsgl,
			 u8 *hashstate)
{
	char vec_name[16];
	unsigned int i;
	int err;

	sprintf(vec_name, "%u", vec_num);

	for (i = 0; i < ARRAY_SIZE(default_hash_testvec_configs); i++) {
		err = test_hash_vec_cfg(driver, vec, vec_name,
					&default_hash_testvec_configs[i],
					req, desc, tsgl, hashstate);
		if (err)
			return err;
	}

#ifdef CONFIG_CRYPTO_MANAGER_EXTRA_TESTS
	if (!noextratests) {
		struct testvec_config cfg;
		char cfgname[TESTVEC_CONFIG_NAMELEN];

		for (i = 0; i < fuzz_iterations; i++) {
			generate_random_testvec_config(&cfg, cfgname,
						       sizeof(cfgname));
			err = test_hash_vec_cfg(driver, vec, vec_name, &cfg,
						req, desc, tsgl, hashstate);
			if (err)
				return err;
			cond_resched();
		}
	}
#endif
	return 0;
}