#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct tr2tls_thread_ctx {int /*<<< orphan*/  nr_open_regions; TYPE_1__ thread_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,int /*<<< orphan*/ ) ; 
 struct tr2tls_thread_ctx* tr2tls_get_self () ; 

void tr2tls_pop_self(void)
{
	struct tr2tls_thread_ctx *ctx = tr2tls_get_self();

	if (!ctx->nr_open_regions)
		BUG("no open regions in thread '%s'", ctx->thread_name.buf);

	ctx->nr_open_regions--;
}