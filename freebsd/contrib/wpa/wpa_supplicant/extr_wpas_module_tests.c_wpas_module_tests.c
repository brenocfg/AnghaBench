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
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ common_module_tests () ; 
 scalar_t__ crypto_module_tests () ; 
 scalar_t__ utils_module_tests () ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wpas_blacklist_module_tests () ; 
 scalar_t__ wps_module_tests () ; 

int wpas_module_tests(void)
{
	int ret = 0;

	wpa_printf(MSG_INFO, "wpa_supplicant module tests");

	if (wpas_blacklist_module_tests() < 0)
		ret = -1;

#ifdef CONFIG_WPS
	if (wps_module_tests() < 0)
		ret = -1;
#endif /* CONFIG_WPS */

	if (utils_module_tests() < 0)
		ret = -1;

	if (common_module_tests() < 0)
		ret = -1;

	if (crypto_module_tests() < 0)
		ret = -1;

	return ret;
}