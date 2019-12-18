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
struct ar_context {int descriptors_bus; int /*<<< orphan*/  regs; int /*<<< orphan*/  ohci; int /*<<< orphan*/  buffer; int /*<<< orphan*/  pointer; } ;

/* Variables and functions */
 unsigned int AR_BUFFERS ; 
 int /*<<< orphan*/  COMMAND_PTR (int /*<<< orphan*/ ) ; 
 int CONTEXT_RUN ; 
 int /*<<< orphan*/  CONTROL_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar_context_link_page (struct ar_context*,unsigned int) ; 
 int /*<<< orphan*/  reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ar_context_run(struct ar_context *ctx)
{
	unsigned int i;

	for (i = 0; i < AR_BUFFERS; i++)
		ar_context_link_page(ctx, i);

	ctx->pointer = ctx->buffer;

	reg_write(ctx->ohci, COMMAND_PTR(ctx->regs), ctx->descriptors_bus | 1);
	reg_write(ctx->ohci, CONTROL_SET(ctx->regs), CONTEXT_RUN);
}