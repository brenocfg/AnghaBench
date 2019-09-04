#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ line_len; char* line; int /*<<< orphan*/  remain_len; } ;
typedef  TYPE_1__ git_parse_ctx ;

/* Variables and functions */
 scalar_t__ git__isspace (char) ; 

int git_parse_advance_ws(git_parse_ctx *ctx)
{
	int ret = -1;

	while (ctx->line_len > 0 &&
		ctx->line[0] != '\n' &&
		git__isspace(ctx->line[0])) {
		ctx->line++;
		ctx->line_len--;
		ctx->remain_len--;
		ret = 0;
	}

	return ret;
}