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
struct stat {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb ;
struct TYPE_4__ {int /*<<< orphan*/  local_objects; int /*<<< orphan*/  indexed_objects; int /*<<< orphan*/  received_objects; int /*<<< orphan*/  total_objects; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_indexer_progress ;
typedef  int /*<<< orphan*/  git_indexer ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  base_obj ; 
 int /*<<< orphan*/  base_obj_len ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_indexer_append (int /*<<< orphan*/ *,unsigned char*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  git_indexer_commit (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_indexer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_indexer_hash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_indexer_new (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int) ; 
 int /*<<< orphan*/  git_repository_odb (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_close (int) ; 
 int p_open (char const*,int /*<<< orphan*/ ) ; 
 int p_read (int,unsigned char*,int) ; 
 int /*<<< orphan*/  p_stat (char const*,struct stat*) ; 
 unsigned char* thin_pack ; 
 int thin_pack_len ; 

void test_pack_indexer__fix_thin(void)
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
	cl_git_pass(git_indexer_append(idx, thin_pack, thin_pack_len, &stats));
	cl_git_pass(git_indexer_commit(idx, &stats));

	cl_assert_equal_i(stats.total_objects, 2);
	cl_assert_equal_i(stats.received_objects, 2);
	cl_assert_equal_i(stats.indexed_objects, 2);
	cl_assert_equal_i(stats.local_objects, 1);

	git_oid_fromstr(&should_id, "fefdb2d740a3a6b6c03a0c7d6ce431c6d5810e13");
	cl_assert_equal_oid(&should_id, git_indexer_hash(idx));

	git_indexer_free(idx);
	git_odb_free(odb);
	git_repository_free(repo);

	/*
	 * The pack's name/hash only tells us what objects there are,
	 * so we need to go through the packfile again in order to
	 * figure out whether we calculated the trailer correctly.
	 */
	{
		unsigned char buffer[128];
		int fd;
		ssize_t read;
		struct stat st;
		const char *name = "pack-fefdb2d740a3a6b6c03a0c7d6ce431c6d5810e13.pack";

		fd = p_open(name, O_RDONLY);
		cl_assert(fd != -1);

		cl_git_pass(p_stat(name, &st));

		cl_git_pass(git_indexer_new(&idx, ".", 0, NULL, NULL));
		read = p_read(fd, buffer, sizeof(buffer));
		cl_assert(read != -1);
		p_close(fd);

		cl_git_pass(git_indexer_append(idx, buffer, read, &stats));
		cl_git_pass(git_indexer_commit(idx, &stats));

		cl_assert_equal_i(stats.total_objects, 3);
		cl_assert_equal_i(stats.received_objects, 3);
		cl_assert_equal_i(stats.indexed_objects, 3);
		cl_assert_equal_i(stats.local_objects, 0);

		git_indexer_free(idx);
	}
}