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
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_entry_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_entry (TYPE_1__**,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_lock (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_open_default (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_transaction_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_transaction_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 

void test_config_global__lock_missing_global_config(void)
{
	git_config *cfg;
	git_config_entry *entry;
	git_transaction *transaction;

	p_unlink("home/.gitconfig"); /* No global config */

	cl_git_pass(git_config_open_default(&cfg));
	cl_git_pass(git_config_lock(&transaction, cfg));
	cl_git_pass(git_config_set_string(cfg, "assertion.fail", "boom"));
	cl_git_pass(git_transaction_commit(transaction));
	git_transaction_free(transaction);

	/* cfg is updated */
	cl_git_pass(git_config_get_entry(&entry, cfg, "assertion.fail"));
	cl_assert_equal_s("boom", entry->value);

	git_config_entry_free(entry);
	git_config_free(cfg);

	/* We can reread the new value from the global config */
	cl_git_pass(git_config_open_default(&cfg));
	cl_git_pass(git_config_get_entry(&entry, cfg, "assertion.fail"));
	cl_assert_equal_s("boom", entry->value);

	git_config_entry_free(entry);
	git_config_free(cfg);
}