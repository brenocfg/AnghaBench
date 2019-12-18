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
typedef  scalar_t__ uint64_t ;
struct ptunit_result {int dummy; } ;
struct pt_bcache_entry {int dummy; } ;
struct bcache_fixture {int /*<<< orphan*/  bcache; } ;
typedef  int /*<<< orphan*/  bce ;

/* Variables and functions */
 scalar_t__ bfix_nentries ; 
 int /*<<< orphan*/  memset (struct pt_bcache_entry*,int,int) ; 
 int pt_bcache_lookup (struct pt_bcache_entry*,int /*<<< orphan*/ ,scalar_t__) ; 
 int pt_bce_is_valid (struct pt_bcache_entry) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result initially_empty(struct bcache_fixture *bfix)
{
	uint64_t index;

	for (index = 0; index < bfix_nentries; ++index) {
		struct pt_bcache_entry bce;
		int status;

		memset(&bce, 0xff, sizeof(bce));

		status = pt_bcache_lookup(&bce, bfix->bcache, index);
		ptu_int_eq(status, 0);

		status = pt_bce_is_valid(bce);
		ptu_int_eq(status, 0);
	}

	return ptu_passed();
}