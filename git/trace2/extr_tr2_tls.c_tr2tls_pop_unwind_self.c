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
struct tr2tls_thread_ctx {int nr_open_regions; } ;

/* Variables and functions */
 struct tr2tls_thread_ctx* tr2tls_get_self () ; 
 int /*<<< orphan*/  tr2tls_pop_self () ; 

void tr2tls_pop_unwind_self(void)
{
	struct tr2tls_thread_ctx *ctx = tr2tls_get_self();

	while (ctx->nr_open_regions > 1)
		tr2tls_pop_self();
}