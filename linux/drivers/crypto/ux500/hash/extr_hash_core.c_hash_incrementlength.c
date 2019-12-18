#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ low_word; int /*<<< orphan*/  high_word; } ;
struct TYPE_4__ {TYPE_1__ length; } ;
struct hash_req_ctx {TYPE_2__ state; } ;

/* Variables and functions */

__attribute__((used)) static void hash_incrementlength(struct hash_req_ctx *ctx, u32 incr)
{
	ctx->state.length.low_word += incr;

	/* Check for wrap-around */
	if (ctx->state.length.low_word < incr)
		ctx->state.length.high_word++;
}