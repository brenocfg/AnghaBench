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
struct test_fixture {int /*<<< orphan*/ * fini; int /*<<< orphan*/  init; } ;
struct ptunit_suite {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfix_init ; 
 int /*<<< orphan*/  cifix_init ; 
 int /*<<< orphan*/  fill ; 
 int /*<<< orphan*/  fill_nomap ; 
 int /*<<< orphan*/  fill_null ; 
 int /*<<< orphan*/  fini_null ; 
 int /*<<< orphan*/  ifix_init ; 
 int /*<<< orphan*/  init_null ; 
 int /*<<< orphan*/  invalidate ; 
 int /*<<< orphan*/  invalidate_null ; 
 int /*<<< orphan*/  ptu_run (struct ptunit_suite,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_run_f (struct ptunit_suite,int /*<<< orphan*/ ,struct test_fixture) ; 
 struct ptunit_suite ptunit_mk_suite (int,char**) ; 
 int ptunit_report (struct ptunit_suite*) ; 
 int /*<<< orphan*/  read ; 
 int /*<<< orphan*/  read_nomap ; 
 int /*<<< orphan*/  read_null ; 
 int /*<<< orphan*/  sfix_init ; 

int main(int argc, char **argv)
{
	struct ptunit_suite suite;
	struct test_fixture sfix, ifix, cfix, cifix;

	sfix.init = sfix_init;
	sfix.fini = NULL;

	ifix.init = ifix_init;
	ifix.fini = NULL;

	cfix.init = cfix_init;
	cfix.fini = NULL;

	cifix.init = cifix_init;
	cifix.fini = NULL;

	suite = ptunit_mk_suite(argc, argv);

	ptu_run(suite, init_null);
	ptu_run(suite, fini_null);
	ptu_run(suite, invalidate_null);
	ptu_run(suite, read_null);
	ptu_run(suite, fill_null);

	ptu_run_f(suite, invalidate, sfix);
	ptu_run_f(suite, invalidate, cfix);

	ptu_run_f(suite, read_nomap, sfix);
	ptu_run_f(suite, read_nomap, ifix);
	ptu_run_f(suite, read_nomap, cfix);
	ptu_run_f(suite, read, cifix);

	ptu_run_f(suite, fill_nomap, sfix);
	ptu_run_f(suite, fill_nomap, cfix);
	ptu_run_f(suite, fill, ifix);
	ptu_run_f(suite, fill, cifix);

	return ptunit_report(&suite);
}