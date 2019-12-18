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
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_tests_run ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int eloop_tests(void)
{
	wpa_printf(MSG_INFO, "schedule eloop tests to be run");

	/*
	 * Cannot return error from these without a significant design change,
	 * so for now, run the tests from a scheduled timeout and require
	 * separate verification of the results from the debug log.
	 */
	eloop_register_timeout(0, 0, eloop_tests_run, NULL, NULL);

	return 0;
}