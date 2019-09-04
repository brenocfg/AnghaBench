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
struct TYPE_3__ {size_t line_len; char* line; } ;
typedef  TYPE_1__ git_parse_ctx ;

/* Variables and functions */
 int GIT_PARSE_PEEK_SKIP_WHITESPACE ; 
 scalar_t__ git__isspace (char) ; 

int git_parse_peek(char *out, git_parse_ctx *ctx, int flags)
{
	size_t remain = ctx->line_len;
	const char *ptr = ctx->line;

	while (remain) {
		char c = *ptr;

		if ((flags & GIT_PARSE_PEEK_SKIP_WHITESPACE) &&
		    git__isspace(c)) {
			remain--;
			ptr++;
			continue;
		}

		*out = c;
		return 0;
	}

	return -1;
}