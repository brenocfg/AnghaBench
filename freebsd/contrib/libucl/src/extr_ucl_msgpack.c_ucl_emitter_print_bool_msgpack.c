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
struct ucl_emitter_functions {int /*<<< orphan*/  ud; int /*<<< orphan*/  (* ucl_emitter_append_character ) (unsigned char const,int,int /*<<< orphan*/ ) ;} ;
struct ucl_emitter_context {struct ucl_emitter_functions* func; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (unsigned char const,int,int /*<<< orphan*/ ) ; 

void
ucl_emitter_print_bool_msgpack (struct ucl_emitter_context *ctx, bool val)
{
	const struct ucl_emitter_functions *func = ctx->func;
	const unsigned char true_ch = 0xc3, false_ch = 0xc2;

	func->ucl_emitter_append_character (val ? true_ch : false_ch, 1, func->ud);
}