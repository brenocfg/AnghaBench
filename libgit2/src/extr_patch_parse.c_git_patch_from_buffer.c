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
typedef  int /*<<< orphan*/  git_patch_parse_ctx ;
typedef  int /*<<< orphan*/  git_patch_options ;
typedef  int /*<<< orphan*/  git_patch ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ *) ; 
 int git_patch_parse (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_parse_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_patch_parse_ctx_init (char const*,size_t,int /*<<< orphan*/  const*) ; 

int git_patch_from_buffer(
	git_patch **out,
	const char *content,
	size_t content_len,
	const git_patch_options *opts)
{
	git_patch_parse_ctx *ctx;
	int error;

	ctx = git_patch_parse_ctx_init(content, content_len, opts);
	GIT_ERROR_CHECK_ALLOC(ctx);

	error = git_patch_parse(out, ctx);

	git_patch_parse_ctx_free(ctx);
	return error;
}