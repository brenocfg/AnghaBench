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
struct nmreq_option {uintptr_t nro_next; } ;
struct TestContext {struct nmreq_option* nr_opt; } ;

/* Variables and functions */

__attribute__((used)) static void
push_option(struct nmreq_option *opt, struct TestContext *ctx)
{
	opt->nro_next = (uintptr_t)ctx->nr_opt;
	ctx->nr_opt   = opt;
}