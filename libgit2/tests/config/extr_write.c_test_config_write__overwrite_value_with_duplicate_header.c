#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ git_config_entry ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char const*,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_entry_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_entry (TYPE_1__**,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,char const*) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char const*,char*) ; 

void test_config_write__overwrite_value_with_duplicate_header(void)
{
	const char *file_name  = "config-duplicate-header";
	const char *entry_name = "remote.origin.url";
	git_config *cfg;
	git_config_entry *entry;

	/* This config can occur after removing and re-adding the origin remote */
	const char *file_content =
		"[remote \"origin\"]\n"		\
		"[branch \"master\"]\n"		\
		"	remote = \"origin\"\n"	\
		"[remote \"origin\"]\n"		\
		"	url = \"foo\"\n";

	/* Write the test config and make sure the expected entry exists */
	cl_git_mkfile(file_name, file_content);
	cl_git_pass(git_config_open_ondisk(&cfg, file_name));
	cl_git_pass(git_config_get_entry(&entry, cfg, entry_name));

	/* Update that entry */
	cl_git_pass(git_config_set_string(cfg, entry_name, "newurl"));

	/* Reopen the file and make sure the entry was updated */
	git_config_entry_free(entry);
	git_config_free(cfg);
	cl_git_pass(git_config_open_ondisk(&cfg, file_name));
	cl_git_pass(git_config_get_entry(&entry, cfg, entry_name));

	cl_assert_equal_s("newurl", entry->value);

	/* Cleanup */
	git_config_entry_free(entry);
	git_config_free(cfg);
}