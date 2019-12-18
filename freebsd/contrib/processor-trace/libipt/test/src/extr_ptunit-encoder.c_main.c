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
 int /*<<< orphan*/  alloc_encoder_null ; 
 int /*<<< orphan*/  encoder_fini_null ; 
 int /*<<< orphan*/  encoder_init_null ; 
 int /*<<< orphan*/  free_encoder_null ; 
 int /*<<< orphan*/  get_config ; 
 int /*<<< orphan*/  get_config_null ; 
 int /*<<< orphan*/  get_offset_init ; 
 int /*<<< orphan*/  get_offset_null ; 
 int /*<<< orphan*/  next_null ; 
 int /*<<< orphan*/  ptu_run (struct ptunit_suite,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_run_f (struct ptunit_suite,int /*<<< orphan*/ ,struct test_fixture) ; 
 struct ptunit_suite ptunit_mk_suite (int,char**) ; 
 int ptunit_report (struct ptunit_suite*) ; 
 int /*<<< orphan*/  sync_set_eos ; 
 int /*<<< orphan*/  sync_set_get_offset ; 
 int /*<<< orphan*/  sync_set_null ; 
 int /*<<< orphan*/  tfix_init ; 

int main(int argc, char **argv)
{
	struct test_fixture tfix;
	struct ptunit_suite suite;

	tfix.init = tfix_init;
	tfix.fini = NULL;

	suite = ptunit_mk_suite(argc, argv);

	ptu_run(suite, encoder_init_null);
	ptu_run(suite, encoder_fini_null);
	ptu_run(suite, alloc_encoder_null);
	ptu_run(suite, free_encoder_null);

	ptu_run(suite, sync_set_null);
	ptu_run_f(suite, sync_set_eos, tfix);

	ptu_run(suite, get_offset_null);
	ptu_run_f(suite, get_offset_init, tfix);
	ptu_run_f(suite, sync_set_get_offset, tfix);

	ptu_run(suite, get_config_null);
	ptu_run_f(suite, get_config, tfix);

	ptu_run(suite, next_null);

	return ptunit_report(&suite);
}