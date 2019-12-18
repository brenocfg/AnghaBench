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
struct pt_bcache_entry {int dummy; } ;
struct bcache_fixture {int /*<<< orphan*/  bcache; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfix_nentries ; 
 int pt_bcache_lookup (struct pt_bcache_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_internal ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result lookup_bad_index(struct bcache_fixture *bfix)
{
	struct pt_bcache_entry bce;
	int errcode;

	errcode = pt_bcache_lookup(&bce, bfix->bcache, bfix_nentries);
	ptu_int_eq(errcode, -pte_internal);

	return ptu_passed();
}