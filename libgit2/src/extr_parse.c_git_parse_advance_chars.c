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
struct TYPE_3__ {size_t line; size_t remain_len; size_t line_len; } ;
typedef  TYPE_1__ git_parse_ctx ;

/* Variables and functions */

void git_parse_advance_chars(git_parse_ctx *ctx, size_t char_cnt)
{
	ctx->line += char_cnt;
	ctx->remain_len -= char_cnt;
	ctx->line_len -= char_cnt;
}