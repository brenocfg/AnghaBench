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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_hash_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_hash_ctx_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_hash_ctx_init (int /*<<< orphan*/ *) ; 
 int git_hash_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_hash_update (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  p_close (int) ; 
 int p_open (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ p_read (int,char*,int) ; 

__attribute__((used)) static int sha1_file(git_oid *oid, const char *filename)
{
	git_hash_ctx ctx;
	char buf[2048];
	int fd, ret;
	ssize_t read_len;

	fd = p_open(filename, O_RDONLY);
	cl_assert(fd >= 0);

	cl_git_pass(git_hash_ctx_init(&ctx));

	while ((read_len = p_read(fd, buf, 2048)) > 0)
		cl_git_pass(git_hash_update(&ctx, buf, (size_t)read_len));

	cl_assert_equal_i(0, read_len);
	p_close(fd);

	ret = git_hash_final(oid, &ctx);
	git_hash_ctx_cleanup(&ctx);

	return ret;
}