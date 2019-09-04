#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  old_path; } ;
typedef  TYPE_2__ git_patch_parsed ;
struct TYPE_7__ {scalar_t__ line_len; } ;
struct TYPE_9__ {TYPE_1__ parse_ctx; } ;
typedef  TYPE_3__ git_patch_parse_ctx ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  git_buf_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int parse_header_path_buf (int /*<<< orphan*/ *,TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static int parse_header_git_oldpath(
	git_patch_parsed *patch, git_patch_parse_ctx *ctx)
{
	git_buf old_path = GIT_BUF_INIT;
	int error;

	if ((error = parse_header_path_buf(&old_path, ctx, ctx->parse_ctx.line_len - 1)) <  0)
		goto out;

	patch->old_path = git_buf_detach(&old_path);

out:
	git_buf_dispose(&old_path);
	return error;
}