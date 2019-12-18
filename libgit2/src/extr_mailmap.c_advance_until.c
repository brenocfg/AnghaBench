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
struct TYPE_4__ {char* line; scalar_t__ line_len; } ;
typedef  TYPE_1__ git_parse_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  git_parse_advance_chars (TYPE_1__*,int) ; 

__attribute__((used)) static int advance_until(
	const char **start, size_t *len, git_parse_ctx *ctx, char needle)
{
	*start = ctx->line;
	while (ctx->line_len > 0 && *ctx->line != '#' && *ctx->line != needle)
		git_parse_advance_chars(ctx, 1);

	if (ctx->line_len == 0 || *ctx->line == '#')
		return -1; /* end of line */

	*len = ctx->line - *start;
	git_parse_advance_chars(ctx, 1); /* advance past needle */
	return 0;
}