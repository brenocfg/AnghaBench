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
struct bcache_fixture {void* fini; int /*<<< orphan*/  init; } ;

/* Variables and functions */
 int /*<<< orphan*/  add ; 
 int /*<<< orphan*/  add_bad_index ; 
 int /*<<< orphan*/  add_null ; 
 int /*<<< orphan*/  alloc ; 
 int /*<<< orphan*/  alloc_min ; 
 int /*<<< orphan*/  alloc_too_big ; 
 int /*<<< orphan*/  alloc_zero ; 
 int /*<<< orphan*/  bcache_entry_size ; 
 int /*<<< orphan*/  bcache_size ; 
 void* bfix_fini ; 
 int /*<<< orphan*/  bfix_init ; 
 unsigned long long bfix_nentries ; 
 int /*<<< orphan*/  cfix_init ; 
 int /*<<< orphan*/  free_null ; 
 int /*<<< orphan*/  initially_empty ; 
 int /*<<< orphan*/  lookup_bad_index ; 
 int /*<<< orphan*/  lookup_null ; 
 int /*<<< orphan*/  ptu_run (struct ptunit_suite,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_run_f (struct ptunit_suite,int /*<<< orphan*/ ,struct bcache_fixture) ; 
 int /*<<< orphan*/  ptu_run_fp (struct ptunit_suite,int /*<<< orphan*/ ,struct bcache_fixture,unsigned long long) ; 
 struct ptunit_suite ptunit_mk_suite (int,char**) ; 
 int ptunit_report (struct ptunit_suite*) ; 
 int /*<<< orphan*/  stress ; 

int main(int argc, char **argv)
{
	struct bcache_fixture bfix, cfix;
	struct ptunit_suite suite;

	bfix.init = bfix_init;
	bfix.fini = bfix_fini;

	cfix.init = cfix_init;
	cfix.fini = bfix_fini;

	suite = ptunit_mk_suite(argc, argv);

	ptu_run(suite, bcache_entry_size);
	ptu_run(suite, bcache_size);

	ptu_run(suite, free_null);
	ptu_run(suite, add_null);
	ptu_run(suite, lookup_null);

	ptu_run_f(suite, alloc, cfix);
	ptu_run_f(suite, alloc_min, cfix);
	ptu_run_f(suite, alloc_too_big, cfix);
	ptu_run_f(suite, alloc_zero, cfix);

	ptu_run_f(suite, initially_empty, bfix);

	ptu_run_f(suite, add_bad_index, bfix);
	ptu_run_f(suite, lookup_bad_index, bfix);

	ptu_run_fp(suite, add, bfix, 0ull);
	ptu_run_fp(suite, add, bfix, bfix_nentries - 1ull);
	ptu_run_f(suite, stress, bfix);

	return ptunit_report(&suite);
}