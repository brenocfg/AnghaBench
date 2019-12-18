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
struct pt_section {int /*<<< orphan*/  size; int /*<<< orphan*/  offset; int /*<<< orphan*/  filename; } ;
struct iscache_fixture {int /*<<< orphan*/  iscache; struct pt_section** section; } ;

/* Variables and functions */
 int pt_iscache_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr (struct pt_section*) ; 

__attribute__((used)) static struct ptunit_result find_empty(struct iscache_fixture *cfix)
{
	struct pt_section *section;
	int found;

	section = cfix->section[0];
	ptu_ptr(section);

	found = pt_iscache_find(&cfix->iscache, section->filename,
				section->offset, section->size, 0ull);
	ptu_int_eq(found, 0);

	return ptu_passed();
}