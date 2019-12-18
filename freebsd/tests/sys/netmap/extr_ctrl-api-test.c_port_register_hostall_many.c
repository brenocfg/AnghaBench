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
struct TestContext {int nr_host_tx_rings; int nr_host_rx_rings; int /*<<< orphan*/  nr_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_REG_SW ; 
 int port_register (struct TestContext*) ; 

__attribute__((used)) static int
port_register_hostall_many(struct TestContext *ctx)
{
	ctx->nr_mode   = NR_REG_SW;
	ctx->nr_host_tx_rings = 5;
	ctx->nr_host_rx_rings = 4;
	return port_register(ctx);
}