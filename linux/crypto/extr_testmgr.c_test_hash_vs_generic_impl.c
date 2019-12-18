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
struct test_sglist {int dummy; } ;
struct shash_desc {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int test_hash_vs_generic_impl(const char *driver,
				     const char *generic_driver,
				     unsigned int maxkeysize,
				     struct ahash_request *req,
				     struct shash_desc *desc,
				     struct test_sglist *tsgl,
				     u8 *hashstate)
{
	return 0;
}