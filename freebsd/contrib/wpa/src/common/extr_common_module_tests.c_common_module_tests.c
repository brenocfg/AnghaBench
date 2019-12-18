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
 scalar_t__ gas_tests () ; 
 scalar_t__ ieee802_11_parse_tests () ; 
 scalar_t__ rsn_ie_parse_tests () ; 
 scalar_t__ sae_tests () ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int common_module_tests(void)
{
	int ret = 0;

	wpa_printf(MSG_INFO, "common module tests");

	if (ieee802_11_parse_tests() < 0 ||
	    gas_tests() < 0 ||
	    sae_tests() < 0 ||
	    rsn_ie_parse_tests() < 0)
		ret = -1;

	return ret;
}