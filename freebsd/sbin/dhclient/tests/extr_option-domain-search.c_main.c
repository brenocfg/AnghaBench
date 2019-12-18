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

/* Variables and functions */
 int /*<<< orphan*/  multiple_domains_valid () ; 
 int /*<<< orphan*/  no_option_present () ; 
 int /*<<< orphan*/  one_domain_truncated1 () ; 
 int /*<<< orphan*/  one_domain_truncated2 () ; 
 int /*<<< orphan*/  one_domain_valid () ; 
 int /*<<< orphan*/  two_domains_compressed () ; 
 int /*<<< orphan*/  two_domains_forwardptr () ; 
 int /*<<< orphan*/  two_domains_infloop () ; 
 int /*<<< orphan*/  two_domains_truncated1 () ; 
 int /*<<< orphan*/  two_domains_truncated2 () ; 
 int /*<<< orphan*/  two_domains_truncatedptr () ; 
 int /*<<< orphan*/  two_domains_valid () ; 

int
main(int argc, char *argv[])
{

	no_option_present();

	one_domain_valid();
	one_domain_truncated1();
	one_domain_truncated2();

	two_domains_valid();
	two_domains_truncated1();
	two_domains_truncated2();

	two_domains_compressed();
	two_domains_infloop();
	two_domains_forwardptr();
	two_domains_truncatedptr();

	multiple_domains_valid();

	return (0);
}