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
 int /*<<< orphan*/ * cfg ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 

void test_config_validkeyname__cleanup(void)
{
	git_config_free(cfg);
	cfg = NULL;

	cl_fixture_cleanup("config10");
}