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
 int /*<<< orphan*/  init ; 
 int /*<<< orphan*/  init_null ; 
 int /*<<< orphan*/  is_empty_initial ; 
 int /*<<< orphan*/  is_empty_no ; 
 int /*<<< orphan*/  is_empty_null ; 
 int /*<<< orphan*/  is_empty_yes ; 
 int /*<<< orphan*/  ptu_run (struct ptunit_suite,int /*<<< orphan*/ ) ; 
 struct ptunit_suite ptunit_mk_suite (int,char**) ; 
 int ptunit_report (struct ptunit_suite*) ; 
 int /*<<< orphan*/  query_empty ; 
 int /*<<< orphan*/  query_not_taken ; 
 int /*<<< orphan*/  query_null ; 
 int /*<<< orphan*/  query_taken ; 
 int /*<<< orphan*/  update_tnt ; 
 int /*<<< orphan*/  update_tnt_not_empty ; 
 int /*<<< orphan*/  update_tnt_null_packet ; 
 int /*<<< orphan*/  update_tnt_null_tnt ; 

int main(int argc, char **argv)
{
	struct ptunit_suite suite;

	suite = ptunit_mk_suite(argc, argv);

	ptu_run(suite, init);
	ptu_run(suite, init_null);
	ptu_run(suite, is_empty_initial);
	ptu_run(suite, is_empty_no);
	ptu_run(suite, is_empty_yes);
	ptu_run(suite, is_empty_null);
	ptu_run(suite, query_taken);
	ptu_run(suite, query_not_taken);
	ptu_run(suite, query_empty);
	ptu_run(suite, query_null);
	ptu_run(suite, update_tnt);
	ptu_run(suite, update_tnt_not_empty);
	ptu_run(suite, update_tnt_null_tnt);
	ptu_run(suite, update_tnt_null_packet);

	return ptunit_report(&suite);
}