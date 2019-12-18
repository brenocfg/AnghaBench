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
typedef  int /*<<< orphan*/  git_vector ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_fetchhead_ref ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_fetchhead_ref_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int,char*,char*) ; 
 int /*<<< orphan*/  git_fetchhead_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_vector_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void populate_fetchhead(git_vector *out, git_repository *repo)
{
	git_fetchhead_ref *fetchhead_ref;
	git_oid oid;

	cl_git_pass(git_oid_fromstr(&oid,
		"49322bb17d3acc9146f98c97d078513228bbf3c0"));
	cl_git_pass(git_fetchhead_ref_create(&fetchhead_ref, &oid, 1,
		"refs/heads/master",
		"git://github.com/libgit2/TestGitRepository"));
	cl_git_pass(git_vector_insert(out, fetchhead_ref));

	cl_git_pass(git_oid_fromstr(&oid,
		"0966a434eb1a025db6b71485ab63a3bfbea520b6"));
	cl_git_pass(git_fetchhead_ref_create(&fetchhead_ref, &oid, 0,
		"refs/heads/first-merge",
		"git://github.com/libgit2/TestGitRepository"));
	cl_git_pass(git_vector_insert(out, fetchhead_ref));

	cl_git_pass(git_oid_fromstr(&oid,
		"42e4e7c5e507e113ebbb7801b16b52cf867b7ce1"));
	cl_git_pass(git_fetchhead_ref_create(&fetchhead_ref, &oid, 0,
		"refs/heads/no-parent",
		"git://github.com/libgit2/TestGitRepository"));
	cl_git_pass(git_vector_insert(out, fetchhead_ref));

	cl_git_pass(git_oid_fromstr(&oid,
		"d96c4e80345534eccee5ac7b07fc7603b56124cb"));
	cl_git_pass(git_fetchhead_ref_create(&fetchhead_ref, &oid, 0,
		"refs/tags/annotated_tag",
		"git://github.com/libgit2/TestGitRepository"));
	cl_git_pass(git_vector_insert(out, fetchhead_ref));

	cl_git_pass(git_oid_fromstr(&oid,
		"55a1a760df4b86a02094a904dfa511deb5655905"));
	cl_git_pass(git_fetchhead_ref_create(&fetchhead_ref, &oid, 0,
		"refs/tags/blob",
		"git://github.com/libgit2/TestGitRepository"));
	cl_git_pass(git_vector_insert(out, fetchhead_ref));

	cl_git_pass(git_oid_fromstr(&oid,
		"8f50ba15d49353813cc6e20298002c0d17b0a9ee"));
	cl_git_pass(git_fetchhead_ref_create(&fetchhead_ref, &oid, 0,
		"refs/tags/commit_tree",
		"git://github.com/libgit2/TestGitRepository"));
	cl_git_pass(git_vector_insert(out, fetchhead_ref));

	cl_git_pass(git_fetchhead_write(repo, out));
}