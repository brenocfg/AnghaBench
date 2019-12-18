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
struct TestContext {int /*<<< orphan*/  nr_mode; } ;

/* Variables and functions */
 scalar_t__ NETMAP_API ; 
 int /*<<< orphan*/  NR_REG_NIC_SW ; 
 int niocregif (struct TestContext*,scalar_t__) ; 

__attribute__((used)) static int
legacy_regif_future(struct TestContext *ctx)
{
	ctx->nr_mode = NR_REG_NIC_SW;
	/* Test forward compatibility for the legacy ABI. This means
	 * using an older kernel (with ABI 12 or higher) and a newer
	 * application (with ABI greater than NETMAP_API). */
	return niocregif(ctx, NETMAP_API+2);
}