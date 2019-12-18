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

/* Variables and functions */
 int test_ahash_vec_cfg (char const*,struct hash_testvec const*,char const*,struct testvec_config const*,struct ahash_request*,struct test_sglist*,int /*<<< orphan*/ *) ; 
 int test_shash_vec_cfg (char const*,struct hash_testvec const*,char const*,struct testvec_config const*,struct shash_desc*,struct test_sglist*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_hash_vec_cfg(const char *driver,
			     const struct hash_testvec *vec,
			     const char *vec_name,
			     const struct testvec_config *cfg,
			     struct ahash_request *req,
			     struct shash_desc *desc,
			     struct test_sglist *tsgl,
			     u8 *hashstate)
{
	int err;

	/*
	 * For algorithms implemented as "shash", most bugs will be detected by
	 * both the shash and ahash tests.  Test the shash API first so that the
	 * failures involve less indirection, so are easier to debug.
	 */

	if (desc) {
		err = test_shash_vec_cfg(driver, vec, vec_name, cfg, desc, tsgl,
					 hashstate);
		if (err)
			return err;
	}

	return test_ahash_vec_cfg(driver, vec, vec_name, cfg, req, tsgl,
				  hashstate);
}