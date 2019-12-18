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
 int /*<<< orphan*/  ptu_run (struct ptunit_suite,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_run_p (struct ptunit_suite,int /*<<< orphan*/ ,int) ; 
 struct ptunit_suite ptunit_mk_suite (int,char**) ; 
 int ptunit_report (struct ptunit_suite*) ; 
 int /*<<< orphan*/  query ; 
 int /*<<< orphan*/  query_initial ; 
 int /*<<< orphan*/  query_noip ; 
 int /*<<< orphan*/  query_null ; 
 int /*<<< orphan*/  query_suppressed ; 
 int /*<<< orphan*/  status ; 
 int /*<<< orphan*/  status_initial ; 
 int /*<<< orphan*/  status_noip ; 
 int /*<<< orphan*/  status_null ; 
 int /*<<< orphan*/  status_suppressed ; 
 int /*<<< orphan*/  update_ip_bad_packet ; 
 int /*<<< orphan*/  update_ip_null_ip ; 
 int /*<<< orphan*/  update_ip_null_packet ; 
 int /*<<< orphan*/  update_ip_sext48 ; 
 int /*<<< orphan*/  update_ip_suppressed ; 
 int /*<<< orphan*/  update_ip_upd16 ; 
 int /*<<< orphan*/  update_ip_upd32 ; 

int main(int argc, char **argv)
{
	struct ptunit_suite suite;

	suite = ptunit_mk_suite(argc, argv);

	ptu_run(suite, init);
	ptu_run(suite, init_null);
	ptu_run(suite, status_initial);
	ptu_run(suite, status);
	ptu_run(suite, status_null);
	ptu_run(suite, status_noip);
	ptu_run(suite, status_suppressed);
	ptu_run(suite, query_initial);
	ptu_run(suite, query);
	ptu_run(suite, query_null);
	ptu_run(suite, query_noip);
	ptu_run(suite, query_suppressed);
	ptu_run_p(suite, update_ip_suppressed, 0);
	ptu_run_p(suite, update_ip_suppressed, 1);
	ptu_run_p(suite, update_ip_upd16, 0);
	ptu_run_p(suite, update_ip_upd16, 1);
	ptu_run_p(suite, update_ip_upd32, 0);
	ptu_run_p(suite, update_ip_upd32, 1);
	ptu_run_p(suite, update_ip_sext48, 0);
	ptu_run_p(suite, update_ip_sext48, 1);
	ptu_run_p(suite, update_ip_bad_packet, 0);
	ptu_run_p(suite, update_ip_bad_packet, 1);
	ptu_run(suite, update_ip_null_ip);
	ptu_run_p(suite, update_ip_null_packet, 0);
	ptu_run_p(suite, update_ip_null_packet, 1);

	return ptunit_report(&suite);
}