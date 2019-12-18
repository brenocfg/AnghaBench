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
struct TestContext {scalar_t__ nr_ringid; int /*<<< orphan*/  nr_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_REG_ONE_NIC ; 
 int port_register (struct TestContext*) ; 

__attribute__((used)) static int
port_register_single_hw_pair(struct TestContext *ctx)
{
	ctx->nr_mode   = NR_REG_ONE_NIC;
	ctx->nr_ringid = 0;
	return port_register(ctx);
}