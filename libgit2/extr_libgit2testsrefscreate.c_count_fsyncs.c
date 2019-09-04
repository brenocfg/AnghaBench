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
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_refdb ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_master_tip ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_refdb_compress (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_refdb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_refdb (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 size_t p_fsync__cnt ; 

__attribute__((used)) static void count_fsyncs(size_t *create_count, size_t *compress_count)
{
	git_reference *ref = NULL;
	git_refdb *refdb;
	git_oid id;

	p_fsync__cnt = 0;

	git_oid_fromstr(&id, current_master_tip);
	cl_git_pass(git_reference_create(&ref, g_repo, "refs/heads/fsync_test", &id, 0, "log message"));
	git_reference_free(ref);

	*create_count = p_fsync__cnt;
	p_fsync__cnt = 0;

	cl_git_pass(git_repository_refdb(&refdb, g_repo));
	cl_git_pass(git_refdb_compress(refdb));
	git_refdb_free(refdb);

	*compress_count = p_fsync__cnt;
	p_fsync__cnt = 0;
}