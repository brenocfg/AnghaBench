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
struct TestContext {int nr_extra_bufs; int /*<<< orphan*/  nr_mode; int /*<<< orphan*/  ifname_ext; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETMAP_API_NIOCREGIF ; 
 int /*<<< orphan*/  NR_REG_ALL_NIC ; 
 int niocregif (struct TestContext*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncat (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
legacy_regif_extra_bufs_pipe(struct TestContext *ctx)
{
	strncat(ctx->ifname_ext, "{pipeexbuf", sizeof(ctx->ifname_ext));
	ctx->nr_mode = NR_REG_ALL_NIC;
	ctx->nr_extra_bufs = 58;	/* arbitrary number of extra bufs */

	return niocregif(ctx, NETMAP_API_NIOCREGIF);
}