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
struct window {int /*<<< orphan*/  data; int /*<<< orphan*/  instructions; int /*<<< orphan*/  out; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void window_release(struct window *ctx)
{
	strbuf_release(&ctx->out);
	strbuf_release(&ctx->instructions);
	strbuf_release(&ctx->data);
}