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
struct th_data {int /*<<< orphan*/  id; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_refdb ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int GIT_ELOCKED ; 
 int NREFS ; 
 int /*<<< orphan*/  cl_git_thread_pass (struct th_data*,int) ; 
 scalar_t__ concurrent_compress ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int git_refdb_compress (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_refdb_free (int /*<<< orphan*/ *) ; 
 int git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int git_repository_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int git_repository_refdb (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_snprintf (char*,int,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void *create_refs(void *arg)
{
	int i, error;
	struct th_data *data = (struct th_data *) arg;
	git_oid head;
	char name[128];
	git_reference *ref[NREFS];
	git_repository *repo;

	cl_git_thread_pass(data, git_repository_open(&repo, data->path));

	do {
		error = git_reference_name_to_id(&head, repo, "HEAD");
	} while (error == GIT_ELOCKED);
	cl_git_thread_pass(data, error);

	for (i = 0; i < NREFS; ++i) {
		p_snprintf(name, sizeof(name), "refs/heads/thread-%03d-%02d", data->id, i);
		do {
			error = git_reference_create(&ref[i], repo, name, &head, 0, NULL);
		} while (error == GIT_ELOCKED);
		cl_git_thread_pass(data, error);

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

	for (i = 0; i < NREFS; ++i)
		git_reference_free(ref[i]);

	git_repository_free(repo);

	git_error_clear();
	return arg;
}