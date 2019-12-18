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
typedef  int /*<<< orphan*/  bce ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pt_bcache_entry*,int /*<<< orphan*/ ,int) ; 
 int pt_bcache_add (int /*<<< orphan*/ *,unsigned long long,struct pt_bcache_entry) ; 
 int /*<<< orphan*/  pte_internal ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result add_null(void)
{
	struct pt_bcache_entry bce;
	int errcode;

	memset(&bce, 0, sizeof(bce));

	errcode = pt_bcache_add(NULL, 0ull, bce);
	ptu_int_eq(errcode, -pte_internal);

	return ptu_passed();
}