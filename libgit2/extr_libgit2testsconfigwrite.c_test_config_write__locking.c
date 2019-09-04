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
typedef  int /*<<< orphan*/  git_transaction ;
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ git_config_entry ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char const*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_entry_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_entry (TYPE_1__**,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_lock (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,char const*) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_transaction_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_transaction_free (int /*<<< orphan*/ *) ; 

void test_config_write__locking(void)
{
	git_config *cfg, *cfg2;
	git_config_entry *entry;
	git_transaction *tx;
	const char *filename = "locked-file";

	/* Open the config and lock it */
	cl_git_mkfile(filename, "[section]\n\tname = value\n");
	cl_git_pass(git_config_open_ondisk(&cfg, filename));
	cl_git_pass(git_config_get_entry(&entry, cfg, "section.name"));
	cl_assert_equal_s("value", entry->value);
	git_config_entry_free(entry);
	cl_git_pass(git_config_lock(&tx, cfg));

	/* Change entries in the locked backend */
	cl_git_pass(git_config_set_string(cfg, "section.name", "other value"));
	cl_git_pass(git_config_set_string(cfg, "section2.name3", "more value"));

	/* We can see that the file we read from hasn't changed */
	cl_git_pass(git_config_open_ondisk(&cfg2, filename));
	cl_git_pass(git_config_get_entry(&entry, cfg2, "section.name"));
	cl_assert_equal_s("value", entry->value);
	git_config_entry_free(entry);
	cl_git_fail_with(GIT_ENOTFOUND, git_config_get_entry(&entry, cfg2, "section2.name3"));
	git_config_free(cfg2);

	/* And we also get the old view when we read from the locked config */
	cl_git_pass(git_config_get_entry(&entry, cfg, "section.name"));
	cl_assert_equal_s("value", entry->value);
	git_config_entry_free(entry);
	cl_git_fail_with(GIT_ENOTFOUND, git_config_get_entry(&entry, cfg, "section2.name3"));

	cl_git_pass(git_transaction_commit(tx));
	git_transaction_free(tx);

	/* Now that we've unlocked it, we should see both updates */
	cl_git_pass(git_config_get_entry(&entry, cfg, "section.name"));
	cl_assert_equal_s("other value", entry->value);
	git_config_entry_free(entry);
	cl_git_pass(git_config_get_entry(&entry, cfg, "section2.name3"));
	cl_assert_equal_s("more value", entry->value);
	git_config_entry_free(entry);

	git_config_free(cfg);

	/* We should also see the changes after reopening the config */
	cl_git_pass(git_config_open_ondisk(&cfg, filename));
	cl_git_pass(git_config_get_entry(&entry, cfg, "section.name"));
	cl_assert_equal_s("other value", entry->value);
	git_config_entry_free(entry);
	cl_git_pass(git_config_get_entry(&entry, cfg, "section2.name3"));
	cl_assert_equal_s("more value", entry->value);
	git_config_entry_free(entry);

	git_config_free(cfg);
}