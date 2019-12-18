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
 int /*<<< orphan*/  TEST_CONFIG ; 
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_unlink (int /*<<< orphan*/ ) ; 

void test_config_stress__cleanup(void)
{
	git_buf_dispose(&buf);
	p_unlink(TEST_CONFIG);
}