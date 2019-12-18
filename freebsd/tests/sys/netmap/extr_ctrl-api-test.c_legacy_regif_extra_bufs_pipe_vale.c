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
 int legacy_regif_extra_bufs_pipe (struct TestContext*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
legacy_regif_extra_bufs_pipe_vale(struct TestContext *ctx)
{
	strncpy(ctx->ifname_ext, "valeX1:Y4", sizeof(ctx->ifname_ext));
	return legacy_regif_extra_bufs_pipe(ctx);
}