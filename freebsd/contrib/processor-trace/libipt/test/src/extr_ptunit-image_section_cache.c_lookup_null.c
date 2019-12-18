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
typedef  int /*<<< orphan*/  uint64_t ;
struct ptunit_result {int dummy; } ;
struct pt_section {int dummy; } ;
struct pt_image_section_cache {int dummy; } ;

/* Variables and functions */
 int pt_iscache_lookup (struct pt_image_section_cache*,struct pt_section**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_internal ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result lookup_null(void)
{
	struct pt_image_section_cache iscache;
	struct pt_section *section;
	uint64_t laddr;
	int errcode;

	errcode = pt_iscache_lookup(NULL, &section, &laddr, 0);
	ptu_int_eq(errcode, -pte_internal);

	errcode = pt_iscache_lookup(&iscache, NULL, &laddr, 0);
	ptu_int_eq(errcode, -pte_internal);

	errcode = pt_iscache_lookup(&iscache, &section, NULL, 0);
	ptu_int_eq(errcode, -pte_internal);

	return ptu_passed();
}