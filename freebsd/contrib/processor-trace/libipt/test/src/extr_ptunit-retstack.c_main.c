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
 int /*<<< orphan*/  full ; 
 int /*<<< orphan*/  init ; 
 int /*<<< orphan*/  init_null ; 
 int /*<<< orphan*/  overflow ; 
 int /*<<< orphan*/  pop ; 
 int /*<<< orphan*/  pop_empty ; 
 int /*<<< orphan*/  pop_null ; 
 int /*<<< orphan*/  ptu_run (struct ptunit_suite,int /*<<< orphan*/ ) ; 
 struct ptunit_suite ptunit_mk_suite (int,char**) ; 
 int ptunit_report (struct ptunit_suite*) ; 
 int /*<<< orphan*/  query ; 
 int /*<<< orphan*/  query_empty ; 
 int /*<<< orphan*/  query_null ; 

int main(int argc, char **argv)
{
	struct ptunit_suite suite;

	suite = ptunit_mk_suite(argc, argv);

	ptu_run(suite, init);
	ptu_run(suite, init_null);
	ptu_run(suite, query);
	ptu_run(suite, query_empty);
	ptu_run(suite, query_null);
	ptu_run(suite, pop);
	ptu_run(suite, pop_empty);
	ptu_run(suite, pop_null);
	ptu_run(suite, full);
	ptu_run(suite, overflow);

	return ptunit_report(&suite);
}