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
struct TYPE_4__ {int line_len; char* line; } ;
typedef  TYPE_1__ git_parse_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  git_parse_advance_line (TYPE_1__*) ; 

int git_parse_advance_nl(git_parse_ctx *ctx)
{
	if (ctx->line_len != 1 || ctx->line[0] != '\n')
		return -1;

	git_parse_advance_line(ctx);
	return 0;
}