#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_patch_parsed ;
struct TYPE_6__ {int /*<<< orphan*/  parse_ctx; } ;
typedef  TYPE_1__ git_patch_parse_ctx ;

/* Variables and functions */
 scalar_t__ git_parse_ctx_contains_s (int /*<<< orphan*/ *,char*) ; 
 int parse_patch_binary (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int parse_patch_binary_nodata (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int parse_patch_hunks (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int parse_patch_body(
	git_patch_parsed *patch, git_patch_parse_ctx *ctx)
{
	if (git_parse_ctx_contains_s(&ctx->parse_ctx, "GIT binary patch"))
		return parse_patch_binary(patch, ctx);
	else if (git_parse_ctx_contains_s(&ctx->parse_ctx, "Binary files "))
		return parse_patch_binary_nodata(patch, ctx);
	else
		return parse_patch_hunks(patch, ctx);
}