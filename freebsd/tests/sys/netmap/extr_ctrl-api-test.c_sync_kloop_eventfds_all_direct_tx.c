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
 int /*<<< orphan*/  NM_OPT_SYNC_KLOOP_DIRECT_TX ; 
 int sync_kloop_eventfds_all_mode (struct TestContext*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sync_kloop_eventfds_all_direct_tx(struct TestContext *ctx)
{
	return sync_kloop_eventfds_all_mode(ctx,
	    NM_OPT_SYNC_KLOOP_DIRECT_TX);
}