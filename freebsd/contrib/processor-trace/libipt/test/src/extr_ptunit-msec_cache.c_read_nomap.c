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
struct test_fixture {int /*<<< orphan*/  image; int /*<<< orphan*/  mcache; } ;
struct ptunit_result {int dummy; } ;
struct pt_mapped_section {int dummy; } ;

/* Variables and functions */
 int pt_msec_cache_read (int /*<<< orphan*/ *,struct pt_mapped_section const**,int /*<<< orphan*/ *,unsigned long long) ; 
 int /*<<< orphan*/  pte_nomap ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_null (struct pt_mapped_section const*) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result read_nomap(struct test_fixture *tfix)
{
	const struct pt_mapped_section *msec;
	int status;

	msec = NULL;

	status = pt_msec_cache_read(&tfix->mcache, &msec, &tfix->image, 0ull);
	ptu_int_eq(status, -pte_nomap);
	ptu_null(msec);

	return ptu_passed();
}