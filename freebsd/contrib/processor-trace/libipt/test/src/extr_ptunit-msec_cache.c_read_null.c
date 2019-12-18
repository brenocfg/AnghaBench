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
struct pt_msec_cache {int dummy; } ;
struct pt_mapped_section {int dummy; } ;
struct pt_image {int dummy; } ;

/* Variables and functions */
 int pt_msec_cache_read (struct pt_msec_cache*,struct pt_mapped_section const**,struct pt_image*,unsigned long long) ; 
 int /*<<< orphan*/  pte_internal ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result read_null(void)
{
	const struct pt_mapped_section *msec;
	struct pt_msec_cache mcache;
	struct pt_image image;
	int status;

	status = pt_msec_cache_read(NULL, &msec, &image, 0ull);
	ptu_int_eq(status, -pte_internal);

	status = pt_msec_cache_read(&mcache, NULL, &image, 0ull);
	ptu_int_eq(status, -pte_internal);

	status = pt_msec_cache_read(&mcache, &msec, NULL, 0ull);
	ptu_int_eq(status, -pte_internal);

	return ptu_passed();
}