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
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  assert_config_value (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_config_stress__comments(void)
{
	git_config *config;

	cl_git_pass(git_config_open_ondisk(&config, cl_fixture("config/config12")));

	assert_config_value(config, "some.section.test2", "hello");
	assert_config_value(config, "some.section.test3", "welcome");
	assert_config_value(config, "some.section.other", "hello! \" ; ; ; ");
	assert_config_value(config, "some.section.other2", "cool! \" # # # ");
	assert_config_value(config, "some.section.multi", "hi, this is a ; multiline comment # with ;\n special chars and other stuff !@#");
	assert_config_value(config, "some.section.multi2", "good, this is a ; multiline comment # with ;\n special chars and other stuff !@#");
	assert_config_value(config, "some.section.back", "this is \ba phrase");

	git_config_free(config);
}