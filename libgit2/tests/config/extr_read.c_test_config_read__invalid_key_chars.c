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
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clean_test_config ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,char*) ; 

void test_config_read__invalid_key_chars(void)
{
	git_config *cfg;

	cl_set_cleanup(&clean_test_config, NULL);
	cl_git_mkfile("./testconfig", "[foo]\n    has_underscore = git2\n");
	cl_git_fail(git_config_open_ondisk(&cfg, "./testconfig"));

	cl_git_rewritefile("./testconfig", "[foo]\n  has/slash = git2\n");
	cl_git_fail(git_config_open_ondisk(&cfg, "./testconfig"));

	cl_git_rewritefile("./testconfig", "[foo]\n  has+plus = git2\n");
	cl_git_fail(git_config_open_ondisk(&cfg, "./testconfig"));

	cl_git_rewritefile("./testconfig", "[no_key]\n  = git2\n");
	cl_git_fail(git_config_open_ondisk(&cfg, "./testconfig"));

	git_config_free(cfg);
}