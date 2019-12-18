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
struct ptunit_result {int dummy; } ;
struct pt_block_cache {int dummy; } ;
struct pt_bcache_entry {int dummy; } ;

/* Variables and functions */
 int pt_bcache_lookup (struct pt_bcache_entry*,struct pt_block_cache*,unsigned long long) ; 
 int /*<<< orphan*/  pte_internal ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result lookup_null(void)
{
	struct pt_bcache_entry bce;
	struct pt_block_cache bcache;
	int errcode;

	errcode = pt_bcache_lookup(&bce, NULL, 0ull);
	ptu_int_eq(errcode, -pte_internal);

	errcode = pt_bcache_lookup(NULL, &bcache, 0ull);
	ptu_int_eq(errcode, -pte_internal);

	return ptu_passed();
}