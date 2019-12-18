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
struct sync_fixture {int /*<<< orphan*/ * fini; int /*<<< orphan*/  init; } ;
struct ptunit_suite {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ptu_run_f (struct ptunit_suite,int /*<<< orphan*/ ,struct sync_fixture) ; 
 struct ptunit_suite ptunit_mk_suite (int,char**) ; 
 int ptunit_report (struct ptunit_suite*) ; 
 int /*<<< orphan*/  sfix_init ; 
 int /*<<< orphan*/  sync_bwd ; 
 int /*<<< orphan*/  sync_bwd_cutoff ; 
 int /*<<< orphan*/  sync_bwd_empty ; 
 int /*<<< orphan*/  sync_bwd_here ; 
 int /*<<< orphan*/  sync_bwd_none ; 
 int /*<<< orphan*/  sync_bwd_null ; 
 int /*<<< orphan*/  sync_bwd_past ; 
 int /*<<< orphan*/  sync_fwd ; 
 int /*<<< orphan*/  sync_fwd_cutoff ; 
 int /*<<< orphan*/  sync_fwd_empty ; 
 int /*<<< orphan*/  sync_fwd_here ; 
 int /*<<< orphan*/  sync_fwd_none ; 
 int /*<<< orphan*/  sync_fwd_null ; 
 int /*<<< orphan*/  sync_fwd_past ; 

int main(int argc, char **argv)
{
	struct sync_fixture sfix;
	struct ptunit_suite suite;

	sfix.init = sfix_init;
	sfix.fini = NULL;

	suite = ptunit_mk_suite(argc, argv);

	ptu_run_f(suite, sync_fwd_null, sfix);
	ptu_run_f(suite, sync_bwd_null, sfix);

	ptu_run_f(suite, sync_fwd_empty, sfix);
	ptu_run_f(suite, sync_bwd_empty, sfix);

	ptu_run_f(suite, sync_fwd_none, sfix);
	ptu_run_f(suite, sync_bwd_none, sfix);

	ptu_run_f(suite, sync_fwd_here, sfix);
	ptu_run_f(suite, sync_bwd_here, sfix);

	ptu_run_f(suite, sync_fwd, sfix);
	ptu_run_f(suite, sync_bwd, sfix);

	ptu_run_f(suite, sync_fwd_past, sfix);
	ptu_run_f(suite, sync_bwd_past, sfix);

	ptu_run_f(suite, sync_fwd_cutoff, sfix);
	ptu_run_f(suite, sync_bwd_cutoff, sfix);

	return ptunit_report(&suite);
}