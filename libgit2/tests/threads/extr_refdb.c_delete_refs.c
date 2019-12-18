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
struct th_data {int id; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_refdb ;

/* Variables and functions */
 int GIT_ELOCKED ; 
 int GIT_ENOTFOUND ; 
 int NREFS ; 
 int /*<<< orphan*/  cl_git_thread_pass (struct th_data*,int) ; 
 scalar_t__ concurrent_compress ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int git_refdb_compress (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_refdb_free (int /*<<< orphan*/ *) ; 
 int git_reference_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int git_repository_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int git_repository_refdb (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_snprintf (char*,int,char*,int,int) ; 

__attribute__((used)) static void *delete_refs(void *arg)
{
	int i, error;
	struct th_data *data = (struct th_data *) arg;
	git_reference *ref;
	char name[128];
	git_repository *repo;

	cl_git_thread_pass(data, git_repository_open(&repo, data->path));

	for (i = 0; i < NREFS; ++i) {
		p_snprintf(
			name, sizeof(name), "refs/heads/thread-%03d-%02d", (data->id) & ~0x3, i);

		if (!git_reference_lookup(&ref, repo, name)) {
			do {
				error = git_reference_delete(ref);
			} while (error == GIT_ELOCKED);
			/* Sometimes we race with other deleter threads */
			if (error == GIT_ENOTFOUND)
				error = 0;

			cl_git_thread_pass(data, error);
			git_reference_free(ref);
		}

		if (concurrent_compress && i == NREFS/2) {
			git_refdb *refdb;
			cl_git_thread_pass(data, git_repository_refdb(&refdb, repo));
			do {
				error = git_refdb_compress(refdb);
			} while (error == GIT_ELOCKED);
			cl_git_thread_pass(data, error);
			git_refdb_free(refdb);
		}
	}

	git_repository_free(repo);
	git_error_clear();
	return arg;
}