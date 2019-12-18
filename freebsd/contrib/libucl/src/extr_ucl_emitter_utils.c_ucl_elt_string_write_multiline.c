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
struct ucl_emitter_functions {int /*<<< orphan*/  ud; int /*<<< orphan*/  (* ucl_emitter_append_len ) (char*,int,int /*<<< orphan*/ ) ;} ;
struct ucl_emitter_context {struct ucl_emitter_functions* func; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (char*,int,int /*<<< orphan*/ ) ; 

void
ucl_elt_string_write_multiline (const char *str, size_t size,
		struct ucl_emitter_context *ctx)
{
	const struct ucl_emitter_functions *func = ctx->func;

	func->ucl_emitter_append_len ("<<EOD\n", sizeof ("<<EOD\n") - 1, func->ud);
	func->ucl_emitter_append_len (str, size, func->ud);
	func->ucl_emitter_append_len ("\nEOD", sizeof ("\nEOD") - 1, func->ud);
}