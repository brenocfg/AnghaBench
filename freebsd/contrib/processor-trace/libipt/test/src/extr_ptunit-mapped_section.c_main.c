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
struct ptunit_suite {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  asid ; 
 int /*<<< orphan*/  asid_null ; 
 int /*<<< orphan*/  begin ; 
 int /*<<< orphan*/  end ; 
 int /*<<< orphan*/  map ; 
 int /*<<< orphan*/  offset ; 
 int /*<<< orphan*/  ptu_run (struct ptunit_suite,int /*<<< orphan*/ ) ; 
 struct ptunit_suite ptunit_mk_suite (int,char**) ; 
 int ptunit_report (struct ptunit_suite*) ; 
 int /*<<< orphan*/  section ; 
 int /*<<< orphan*/  section_null ; 
 int /*<<< orphan*/  size ; 
 int /*<<< orphan*/  unmap ; 

int main(int argc, char **argv)
{
	struct ptunit_suite suite;

	suite = ptunit_mk_suite(argc, argv);

	ptu_run(suite, begin);
	ptu_run(suite, end);
	ptu_run(suite, offset);
	ptu_run(suite, size);
	ptu_run(suite, asid);
	ptu_run(suite, asid_null);
	ptu_run(suite, map);
	ptu_run(suite, unmap);
	ptu_run(suite, section);
	ptu_run(suite, section_null);

	return ptunit_report(&suite);
}