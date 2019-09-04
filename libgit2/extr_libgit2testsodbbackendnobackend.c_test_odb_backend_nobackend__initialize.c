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
typedef  int /*<<< orphan*/  git_refdb ;
typedef  int /*<<< orphan*/  git_odb ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_refdb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_refdb_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_set_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_set_odb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_set_refdb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void test_odb_backend_nobackend__initialize(void)
{
	git_config *config;
	git_odb *odb;
	git_refdb *refdb;

	cl_git_pass(git_repository_new(&_repo));
	cl_git_pass(git_config_new(&config));
	cl_git_pass(git_odb_new(&odb));
	cl_git_pass(git_refdb_new(&refdb, _repo));

	git_repository_set_config(_repo, config);
	git_repository_set_odb(_repo, odb);
	git_repository_set_refdb(_repo, refdb);

	/* The set increases the refcount and we don't want them anymore */
	git_config_free(config);
	git_odb_free(odb);
	git_refdb_free(refdb);
}