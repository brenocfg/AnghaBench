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
struct TestContext {int /*<<< orphan*/  ifname_ext; } ;

/* Variables and functions */
 int pools_info_get (struct TestContext*) ; 
 int /*<<< orphan*/  strncat (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
pipe_pools_info_get(struct TestContext *ctx)
{
	strncat(ctx->ifname_ext, "{xid", sizeof(ctx->ifname_ext));

	return pools_info_get(ctx);
}