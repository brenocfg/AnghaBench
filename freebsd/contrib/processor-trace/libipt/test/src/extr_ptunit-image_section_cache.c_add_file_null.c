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
struct pt_image_section_cache {int dummy; } ;

/* Variables and functions */
 int pt_iscache_add_file (struct pt_image_section_cache*,char*,unsigned long long,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  pte_invalid ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result add_file_null(void)
{
	struct pt_image_section_cache iscache;
	int errcode;

	errcode = pt_iscache_add_file(NULL, "filename", 0ull, 0ull, 0ull);
	ptu_int_eq(errcode, -pte_invalid);

	errcode = pt_iscache_add_file(&iscache, NULL, 0ull, 0ull, 0ull);
	ptu_int_eq(errcode, -pte_invalid);

	return ptu_passed();
}