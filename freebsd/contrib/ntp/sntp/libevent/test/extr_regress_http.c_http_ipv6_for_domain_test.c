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
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  http_ipv6_for_domain_test_impl (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
http_ipv6_for_domain_test(void *arg)
{
	http_ipv6_for_domain_test_impl(arg, AF_UNSPEC);
}