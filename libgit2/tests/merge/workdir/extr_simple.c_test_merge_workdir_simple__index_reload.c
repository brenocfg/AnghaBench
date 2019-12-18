#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {char* path; int /*<<< orphan*/  id; int /*<<< orphan*/  mode; TYPE_1__ member_0; } ;
typedef  TYPE_2__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEMODE_BLOB ; 
 char* THEIRS_SIMPLE_OID ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_annotated_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_annotated_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_merge (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  repo_index ; 

void test_merge_workdir_simple__index_reload(void)
{
	git_repository *tmp_repo;
	git_annotated_commit *their_heads[1];
	git_oid their_oid;
	git_index_entry entry = {{0}};
	git_index *tmp_index;

	cl_git_pass(git_repository_open(&tmp_repo, git_repository_workdir(repo)));
	cl_git_pass(git_repository_index(&tmp_index, tmp_repo));
	cl_git_pass(git_index_read(repo_index, 0));

	entry.mode = GIT_FILEMODE_BLOB;
	cl_git_pass(git_oid_fromstr(&entry.id, "11deab00b2d3a6f5a3073988ac050c2d7b6655e2"));
	entry.path = "automergeable.txt";
	cl_git_pass(git_index_add(repo_index, &entry));

	cl_git_pass(git_index_add_bypath(tmp_index, "automergeable.txt"));
	cl_git_pass(git_index_write(tmp_index));

	cl_git_pass(git_oid_fromstr(&their_oid, THEIRS_SIMPLE_OID));
	cl_git_pass(git_annotated_commit_lookup(&their_heads[0], repo, &their_oid));
	cl_git_pass(git_merge(repo, (const git_annotated_commit **)their_heads, 1, NULL, NULL));

	git_index_free(tmp_index);
	git_repository_free(tmp_repo);
	git_annotated_commit_free(their_heads[0]);
}