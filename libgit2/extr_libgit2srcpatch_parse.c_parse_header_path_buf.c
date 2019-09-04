#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  line; } ;
struct TYPE_10__ {TYPE_6__ parse_ctx; } ;
typedef  TYPE_1__ git_patch_parse_ctx ;
struct TYPE_11__ {scalar_t__ size; char* ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 int git_buf_put (TYPE_2__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  git_buf_rtrim (TYPE_2__*) ; 
 int git_buf_unquote (TYPE_2__*) ; 
 int /*<<< orphan*/  git_parse_advance_chars (TYPE_6__*,size_t) ; 
 int /*<<< orphan*/  git_path_squash_slashes (TYPE_2__*) ; 

__attribute__((used)) static int parse_header_path_buf(git_buf *path, git_patch_parse_ctx *ctx, size_t path_len)
{
	int error;

	if ((error = git_buf_put(path, ctx->parse_ctx.line, path_len)) < 0)
		goto done;

	git_parse_advance_chars(&ctx->parse_ctx, path_len);

	git_buf_rtrim(path);

	if (path->size > 0 && path->ptr[0] == '"')
		error = git_buf_unquote(path);

	if (error < 0)
		goto done;

	git_path_squash_slashes(path);

done:
	return error;
}