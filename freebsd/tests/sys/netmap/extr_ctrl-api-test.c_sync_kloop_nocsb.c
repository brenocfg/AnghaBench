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
struct TestContext {int dummy; } ;

/* Variables and functions */
 int port_register_hwall (struct TestContext*) ; 
 scalar_t__ sync_kloop_start_stop (struct TestContext*) ; 

__attribute__((used)) static int
sync_kloop_nocsb(struct TestContext *ctx)
{
	int ret;

	ret = port_register_hwall(ctx);
	if (ret != 0) {
		return ret;
	}

	/* Sync kloop must fail because we did not use
	 * NETMAP_REQ_CSB_ENABLE. */
	return sync_kloop_start_stop(ctx) != 0 ? 0 : -1;
}