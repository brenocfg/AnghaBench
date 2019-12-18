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
 int /*<<< orphan*/  EVDNS_BASE_DISABLE_WHEN_INACTIVE ; 
 int /*<<< orphan*/  dns_reissue_test_impl (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dns_reissue_disable_when_inactive_test(void *arg)
{
	dns_reissue_test_impl(arg, EVDNS_BASE_DISABLE_WHEN_INACTIVE);
}