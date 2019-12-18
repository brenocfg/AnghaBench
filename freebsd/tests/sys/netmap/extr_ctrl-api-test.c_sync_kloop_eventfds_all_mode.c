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
typedef  int /*<<< orphan*/  uint32_t ;
struct TestContext {int /*<<< orphan*/  sync_kloop_mode; } ;

/* Variables and functions */
 int csb_mode (struct TestContext*) ; 
 int sync_kloop_eventfds (struct TestContext*) ; 

__attribute__((used)) static int
sync_kloop_eventfds_all_mode(struct TestContext *ctx,
			     uint32_t sync_kloop_mode)
{
	int ret;

	ret = csb_mode(ctx);
	if (ret != 0) {
		return ret;
	}

	ctx->sync_kloop_mode = sync_kloop_mode;

	return sync_kloop_eventfds(ctx);
}