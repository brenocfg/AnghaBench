#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_indexer_progress ;
typedef  int /*<<< orphan*/  git_hash_ctx ;
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  _indexer ; 
 int /*<<< orphan*/  _packbuilder ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  feed_indexer ; 
 int /*<<< orphan*/  git_buf_cstr (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_printf (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  git_futils_readbuffer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_hash_ctx_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_hash_ctx_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_hash_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_hash_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_indexer_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_indexer_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_indexer_new (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fmt (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_packbuilder_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seed_packbuilder () ; 

void test_pack_packbuilder__create_pack(void)
{
	git_indexer_progress stats;
	git_buf buf = GIT_BUF_INIT, path = GIT_BUF_INIT;
	git_hash_ctx ctx;
	git_oid hash;
	char hex[GIT_OID_HEXSZ+1]; hex[GIT_OID_HEXSZ] = '\0';

	seed_packbuilder();

	cl_git_pass(git_indexer_new(&_indexer, ".", 0, NULL, NULL));
	cl_git_pass(git_packbuilder_foreach(_packbuilder, feed_indexer, &stats));
	cl_git_pass(git_indexer_commit(_indexer, &stats));

	git_oid_fmt(hex, git_indexer_hash(_indexer));
	git_buf_printf(&path, "pack-%s.pack", hex);

	/*
	 * By default, packfiles are created with only one thread.
	 * Therefore we can predict the object ordering and make sure
	 * we create exactly the same pack as git.git does when *not*
	 * reusing existing deltas (as libgit2).
	 *
	 * $ cd tests/resources/testrepo.git
	 * $ git rev-list --objects HEAD | \
	 * 	git pack-objects -q --no-reuse-delta --threads=1 pack
	 * $ sha1sum pack-7f5fa362c664d68ba7221259be1cbd187434b2f0.pack
	 * 5d410bdf97cf896f9007681b92868471d636954b
	 *
	 */

	cl_git_pass(git_futils_readbuffer(&buf, git_buf_cstr(&path)));

	cl_git_pass(git_hash_ctx_init(&ctx));
	cl_git_pass(git_hash_update(&ctx, buf.ptr, buf.size));
	cl_git_pass(git_hash_final(&hash, &ctx));
	git_hash_ctx_cleanup(&ctx);

	git_buf_dispose(&path);
	git_buf_dispose(&buf);

	git_oid_fmt(hex, &hash);

	cl_assert_equal_s(hex, "5d410bdf97cf896f9007681b92868471d636954b");
}