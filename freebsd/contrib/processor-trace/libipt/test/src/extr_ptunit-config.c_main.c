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
 int /*<<< orphan*/  addr_filter_0 ; 
 int /*<<< orphan*/  addr_filter_1_3 ; 
 int /*<<< orphan*/  addr_filter_ip_in ; 
 int /*<<< orphan*/  addr_filter_ip_in_stop_in ; 
 int /*<<< orphan*/  addr_filter_ip_out ; 
 int /*<<< orphan*/  addr_filter_ip_out_stop_in ; 
 int /*<<< orphan*/  addr_filter_none ; 
 int /*<<< orphan*/  addr_filter_oob ; 
 int /*<<< orphan*/  addr_filter_size ; 
 int /*<<< orphan*/  addr_filter_stop_in ; 
 int /*<<< orphan*/  addr_filter_stop_out ; 
 int /*<<< orphan*/  cpu_errata_bad_cpuid ; 
 int /*<<< orphan*/  cpu_errata_bad_vendor ; 
 int /*<<< orphan*/  cpu_errata_null ; 
 int /*<<< orphan*/  cpu_errata_unknown ; 
 int /*<<< orphan*/  from_user ; 
 int /*<<< orphan*/  from_user_bad_buffer ; 
 int /*<<< orphan*/  from_user_big ; 
 int /*<<< orphan*/  from_user_null ; 
 int /*<<< orphan*/  from_user_small ; 
 int /*<<< orphan*/  from_user_too_small ; 
 int /*<<< orphan*/  ptu_run (struct ptunit_suite,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_run_p (struct ptunit_suite,int /*<<< orphan*/ ,int) ; 
 struct ptunit_suite ptunit_mk_suite (int,char**) ; 
 int ptunit_report (struct ptunit_suite*) ; 
 int /*<<< orphan*/  size ; 

int main(int argc, char **argv)
{
	struct ptunit_suite suite;

	suite = ptunit_mk_suite(argc, argv);

	ptu_run(suite, from_user_null);
	ptu_run(suite, from_user_too_small);
	ptu_run(suite, from_user_bad_buffer);
	ptu_run(suite, from_user);
	ptu_run(suite, from_user_small);
	ptu_run(suite, from_user_big);
	ptu_run(suite, size);

	ptu_run(suite, addr_filter_size);
	ptu_run(suite, addr_filter_none);
	ptu_run(suite, addr_filter_0);
	ptu_run(suite, addr_filter_1_3);
	ptu_run_p(suite, addr_filter_oob, 255);
	ptu_run_p(suite, addr_filter_oob, 8);

	ptu_run(suite, addr_filter_ip_in);
	ptu_run(suite, addr_filter_ip_out);
	ptu_run(suite, addr_filter_stop_in);
	ptu_run(suite, addr_filter_stop_out);
	ptu_run(suite, addr_filter_ip_out_stop_in);
	ptu_run(suite, addr_filter_ip_in_stop_in);

	ptu_run(suite, cpu_errata_null);
	ptu_run(suite, cpu_errata_unknown);
	ptu_run(suite, cpu_errata_bad_vendor);
	ptu_run(suite, cpu_errata_bad_cpuid);

	return ptunit_report(&suite);
}