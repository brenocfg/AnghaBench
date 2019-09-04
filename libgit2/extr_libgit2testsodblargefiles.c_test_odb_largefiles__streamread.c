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
typedef  int /*<<< orphan*/  hdr ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb_stream ;
typedef  int /*<<< orphan*/  git_object_t ;
typedef  int /*<<< orphan*/  git_hash_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  LARGEFILE_SIZE ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_is_env_set (char*) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  git_hash_ctx_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_hash_ctx_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_hash_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_hash_update (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_odb__format_object_header (size_t*,char*,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_open_rstream (int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_stream_free (int /*<<< orphan*/ *) ; 
 int git_odb_stream_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  odb ; 
 int /*<<< orphan*/  writefile (int /*<<< orphan*/ *) ; 

void test_odb_largefiles__streamread(void)
{
	git_oid oid, read_oid;
	git_odb_stream *stream;
	char buf[10240];
	char hdr[64];
	size_t len, hdr_len, total = 0;
	git_hash_ctx hash;
	git_object_t type;
	int ret;

#ifndef GIT_ARCH_64
	cl_skip();
#endif

	if (!cl_is_env_set("GITTEST_INVASIVE_FS_SIZE") ||
		!cl_is_env_set("GITTEST_SLOW"))
		cl_skip();

	writefile(&oid);

	cl_git_pass(git_odb_open_rstream(&stream, &len, &type, odb, &oid));

	cl_assert_equal_sz(LARGEFILE_SIZE, len);
	cl_assert_equal_i(GIT_OBJECT_BLOB, type);

	cl_git_pass(git_hash_ctx_init(&hash));
	cl_git_pass(git_odb__format_object_header(&hdr_len, hdr, sizeof(hdr), len, type));

	cl_git_pass(git_hash_update(&hash, hdr, hdr_len));

	while ((ret = git_odb_stream_read(stream, buf, 10240)) > 0) {
		cl_git_pass(git_hash_update(&hash, buf, ret));
		total += ret;
	}

	cl_assert_equal_sz(LARGEFILE_SIZE, total);

	git_hash_final(&read_oid, &hash);

	cl_assert_equal_oid(&oid, &read_oid);

	git_hash_ctx_cleanup(&hash);
	git_odb_stream_free(stream);
}