#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t line_len; char* line; } ;
struct TYPE_4__ {TYPE_3__ parse_ctx; } ;
typedef  TYPE_1__ git_patch_parse_ctx ;

/* Variables and functions */
 scalar_t__ git__isspace (char) ; 
 int git_parse_ctx_contains_s (TYPE_3__*,char*) ; 

__attribute__((used)) static size_t header_path_len(git_patch_parse_ctx *ctx)
{
	bool inquote = 0;
	bool quoted = git_parse_ctx_contains_s(&ctx->parse_ctx, "\"");
	size_t len;

	for (len = quoted; len < ctx->parse_ctx.line_len; len++) {
		if (!quoted && git__isspace(ctx->parse_ctx.line[len]))
			break;
		else if (quoted && !inquote && ctx->parse_ctx.line[len] == '"') {
			len++;
			break;
		}

		inquote = (!inquote && ctx->parse_ctx.line[len] == '\\');
	}

	return len;
}