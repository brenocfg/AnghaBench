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
struct TestContext {int nr_num_polling_cpus; scalar_t__ nr_first_cpu_id; int /*<<< orphan*/  nr_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETMAP_POLLING_MODE_SINGLE_CPU ; 
 int vale_attach (struct TestContext*) ; 
 int vale_detach (struct TestContext*) ; 
 int vale_polling_disable (struct TestContext*) ; 
 int vale_polling_enable (struct TestContext*) ; 

__attribute__((used)) static int
vale_polling_enable_disable(struct TestContext *ctx)
{
	int ret = 0;

	if ((ret = vale_attach(ctx)) != 0) {
		return ret;
	}

	ctx->nr_mode             = NETMAP_POLLING_MODE_SINGLE_CPU;
	ctx->nr_num_polling_cpus = 1;
	ctx->nr_first_cpu_id     = 0;
	if ((ret = vale_polling_enable(ctx))) {
		vale_detach(ctx);
#ifdef __FreeBSD__
		/* NETMAP_REQ_VALE_POLLING_DISABLE is disabled on FreeBSD,
		 * because it is currently broken. We are happy to see that
		 * it fails. */
		return 0;
#else
		return ret;
#endif
	}

	if ((ret = vale_polling_disable(ctx))) {
		vale_detach(ctx);
		return ret;
	}

	return vale_detach(ctx);
}