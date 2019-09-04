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
 int /*<<< orphan*/  GIT_REMOTE_DOWNLOAD_TAGS_ALL ; 
 int /*<<< orphan*/  GIT_REMOTE_DOWNLOAD_TAGS_AUTO ; 
 int /*<<< orphan*/  GIT_REMOTE_DOWNLOAD_TAGS_NONE ; 
 int /*<<< orphan*/  _remote ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  assert_config_entry_existence (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  assert_config_entry_value (int /*<<< orphan*/ ,char*,char*) ; 
 char* git_remote_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_set_autotag (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

void test_network_remote_remotes__tagopt(void)
{
	const char *name = git_remote_name(_remote);

	git_remote_set_autotag(_repo, name, GIT_REMOTE_DOWNLOAD_TAGS_ALL);
	assert_config_entry_value(_repo, "remote.test.tagopt", "--tags");

	git_remote_set_autotag(_repo, name, GIT_REMOTE_DOWNLOAD_TAGS_NONE);
	assert_config_entry_value(_repo, "remote.test.tagopt", "--no-tags");

	git_remote_set_autotag(_repo, name, GIT_REMOTE_DOWNLOAD_TAGS_AUTO);
	assert_config_entry_existence(_repo, "remote.test.tagopt", false);
}