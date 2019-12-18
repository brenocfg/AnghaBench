#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_indexer_progress ;
typedef  int /*<<< orphan*/  git_indexer ;
struct TYPE_6__ {int /*<<< orphan*/  klass; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_ZLIB ; 
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  base_obj ; 
 int /*<<< orphan*/  base_obj_len ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  corrupt_thin_pack ; 
 int /*<<< orphan*/  corrupt_thin_pack_len ; 
 TYPE_4__* git_error_last () ; 
 int /*<<< orphan*/  git_indexer_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_indexer_commit (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_indexer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_indexer_new (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int) ; 
 int /*<<< orphan*/  git_repository_odb (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

void test_pack_indexer__corrupt_length(void)
{
	git_indexer *idx = NULL;
	git_indexer_progress stats = { 0 };
	git_repository *repo;
	git_odb *odb;
	git_oid id, should_id;

	cl_git_pass(git_repository_init(&repo, "thin.git", true));
	cl_git_pass(git_repository_odb(&odb, repo));

	/* Store the missing base into your ODB so the indexer can fix the pack */
	cl_git_pass(git_odb_write(&id, odb, base_obj, base_obj_len, GIT_OBJECT_BLOB));
	git_oid_fromstr(&should_id, "e68fe8129b546b101aee9510c5328e7f21ca1d18");
	cl_assert_equal_oid(&should_id, &id);

	cl_git_pass(git_indexer_new(&idx, ".", 0, odb, NULL));
	cl_git_pass(git_indexer_append(
		idx, corrupt_thin_pack, corrupt_thin_pack_len, &stats));
	cl_git_fail(git_indexer_commit(idx, &stats));

	cl_assert(git_error_last() != NULL);
	cl_assert_equal_i(git_error_last()->klass, GIT_ERROR_ZLIB);

	git_indexer_free(idx);
	git_odb_free(odb);
	git_repository_free(repo);
}