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
 int /*<<< orphan*/  cpu_incomplete ; 
 int /*<<< orphan*/  cpu_invalid ; 
 int /*<<< orphan*/  cpu_null ; 
 int /*<<< orphan*/  cpu_valid ; 
 int /*<<< orphan*/  ptu_run (struct ptunit_suite,int /*<<< orphan*/ ) ; 
 struct ptunit_suite ptunit_mk_suite (int,char**) ; 
 int ptunit_report (struct ptunit_suite*) ; 

int main(int argc, char **argv)
{
	struct ptunit_suite suite;

	suite = ptunit_mk_suite(argc, argv);

	ptu_run(suite, cpu_valid);
	ptu_run(suite, cpu_null);
	ptu_run(suite, cpu_incomplete);
	ptu_run(suite, cpu_invalid);

	return ptunit_report(&suite);
}