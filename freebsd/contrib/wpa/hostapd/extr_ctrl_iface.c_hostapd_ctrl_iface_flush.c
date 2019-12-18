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
struct hapd_interfaces {int /*<<< orphan*/  dpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPP_TEST_DISABLED ; 
 int /*<<< orphan*/  dpp_global_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpp_test ; 
 scalar_t__ wps_corrupt_pkhash ; 
 scalar_t__ wps_testing_dummy_cred ; 
 int wps_version_number ; 

__attribute__((used)) static void hostapd_ctrl_iface_flush(struct hapd_interfaces *interfaces)
{
#ifdef CONFIG_WPS_TESTING
	wps_version_number = 0x20;
	wps_testing_dummy_cred = 0;
	wps_corrupt_pkhash = 0;
#endif /* CONFIG_WPS_TESTING */

#ifdef CONFIG_TESTING_OPTIONS
#ifdef CONFIG_DPP
	dpp_test = DPP_TEST_DISABLED;
#endif /* CONFIG_DPP */
#endif /* CONFIG_TESTING_OPTIONS */

#ifdef CONFIG_DPP
	dpp_global_clear(interfaces->dpp);
#endif /* CONFIG_DPP */
}