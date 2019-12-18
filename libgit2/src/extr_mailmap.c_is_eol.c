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
typedef  int /*<<< orphan*/  git_parse_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_PARSE_PEEK_SKIP_WHITESPACE ; 
 scalar_t__ git_parse_peek (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_eol(git_parse_ctx *ctx)
{
	char c;
	return git_parse_peek(&c, ctx, GIT_PARSE_PEEK_SKIP_WHITESPACE) < 0 || c == '#';
}