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
struct time_fixture {int /*<<< orphan*/ * fini; int /*<<< orphan*/  init; } ;
struct ptunit_suite {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cbr ; 
 int /*<<< orphan*/  cbr_null ; 
 int /*<<< orphan*/  cbr_zero ; 
 int /*<<< orphan*/  cyc ; 
 int /*<<< orphan*/  cyc_null ; 
 int /*<<< orphan*/  mtc ; 
 int /*<<< orphan*/  mtc_null ; 
 int /*<<< orphan*/  ptu_run_f (struct ptunit_suite,int /*<<< orphan*/ ,struct time_fixture) ; 
 struct ptunit_suite ptunit_mk_suite (int,char**) ; 
 int ptunit_report (struct ptunit_suite*) ; 
 int /*<<< orphan*/  query_cbr_none ; 
 int /*<<< orphan*/  query_cbr_null ; 
 int /*<<< orphan*/  query_tsc_none ; 
 int /*<<< orphan*/  query_tsc_null ; 
 int /*<<< orphan*/  tcal_cbr_null ; 
 int /*<<< orphan*/  tcal_cbr_zero ; 
 int /*<<< orphan*/  tcal_cyc_null ; 
 int /*<<< orphan*/  tcal_mtc_null ; 
 int /*<<< orphan*/  tfix_init ; 
 int /*<<< orphan*/  tma ; 
 int /*<<< orphan*/  tma_null ; 
 int /*<<< orphan*/  tsc ; 
 int /*<<< orphan*/  tsc_null ; 

int main(int argc, char **argv)
{
	struct ptunit_suite suite;
	struct time_fixture tfix;

	suite = ptunit_mk_suite(argc, argv);

	tfix.init = tfix_init;
	tfix.fini = NULL;

	ptu_run_f(suite, tsc_null, tfix);
	ptu_run_f(suite, cbr_null, tfix);
	ptu_run_f(suite, tma_null, tfix);
	ptu_run_f(suite, mtc_null, tfix);
	ptu_run_f(suite, cyc_null, tfix);

	ptu_run_f(suite, query_tsc_null, tfix);
	ptu_run_f(suite, query_tsc_none, tfix);
	ptu_run_f(suite, query_cbr_null, tfix);
	ptu_run_f(suite, query_cbr_none, tfix);

	ptu_run_f(suite, tcal_cbr_null, tfix);
	ptu_run_f(suite, tcal_cbr_zero, tfix);
	ptu_run_f(suite, tcal_mtc_null, tfix);
	ptu_run_f(suite, tcal_cyc_null, tfix);

	ptu_run_f(suite, tsc, tfix);
	ptu_run_f(suite, cbr, tfix);
	ptu_run_f(suite, cbr_zero, tfix);
	ptu_run_f(suite, tma, tfix);
	ptu_run_f(suite, mtc, tfix);
	ptu_run_f(suite, cyc, tfix);

	/* The bulk is covered in ptt tests. */

	return ptunit_report(&suite);
}