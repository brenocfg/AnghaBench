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
struct TYPE_4__ {size_t line_len; int /*<<< orphan*/  line; } ;
typedef  TYPE_1__ git_parse_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  git_parse_advance_chars (TYPE_1__*,size_t) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char const*,size_t) ; 

int git_parse_advance_expected(
	git_parse_ctx *ctx,
	const char *expected,
	size_t expected_len)
{
	if (ctx->line_len < expected_len)
		return -1;

	if (memcmp(ctx->line, expected, expected_len) != 0)
		return -1;

	git_parse_advance_chars(ctx, expected_len);
	return 0;
}