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
 int /*<<< orphan*/  from_user ; 
 int /*<<< orphan*/  from_user_big ; 
 int /*<<< orphan*/  from_user_cr3 ; 
 int /*<<< orphan*/  from_user_default ; 
 int /*<<< orphan*/  from_user_null ; 
 int /*<<< orphan*/  from_user_small ; 
 int /*<<< orphan*/  match ; 
 int /*<<< orphan*/  match_cr3 ; 
 int /*<<< orphan*/  match_cr3_false ; 
 int /*<<< orphan*/  match_default ; 
 int /*<<< orphan*/  match_default_mixed ; 
 int /*<<< orphan*/  match_null ; 
 int /*<<< orphan*/  match_vmcs ; 
 int /*<<< orphan*/  match_vmcs_false ; 
 int /*<<< orphan*/  ptu_run (struct ptunit_suite,int /*<<< orphan*/ ) ; 
 struct ptunit_suite ptunit_mk_suite (int,char**) ; 
 int ptunit_report (struct ptunit_suite*) ; 
 int /*<<< orphan*/  to_user ; 
 int /*<<< orphan*/  to_user_big ; 
 int /*<<< orphan*/  to_user_cr3 ; 
 int /*<<< orphan*/  to_user_null ; 
 int /*<<< orphan*/  to_user_small ; 
 int /*<<< orphan*/  to_user_too_small ; 

int main(int argc, char **argv)
{
	struct ptunit_suite suite;

	suite = ptunit_mk_suite(argc, argv);

	ptu_run(suite, from_user_null);
	ptu_run(suite, from_user_default);
	ptu_run(suite, from_user_small);
	ptu_run(suite, from_user_big);
	ptu_run(suite, from_user);
	ptu_run(suite, from_user_cr3);

	ptu_run(suite, to_user_null);
	ptu_run(suite, to_user_too_small);
	ptu_run(suite, to_user_small);
	ptu_run(suite, to_user_big);
	ptu_run(suite, to_user);
	ptu_run(suite, to_user_cr3);

	ptu_run(suite, match_null);
	ptu_run(suite, match_default);
	ptu_run(suite, match_default_mixed);
	ptu_run(suite, match_cr3);
	ptu_run(suite, match_vmcs);
	ptu_run(suite, match);
	ptu_run(suite, match_cr3_false);
	ptu_run(suite, match_vmcs_false);

	return ptunit_report(&suite);
}