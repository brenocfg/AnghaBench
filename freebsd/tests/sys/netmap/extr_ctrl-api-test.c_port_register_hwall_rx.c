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
struct TestContext {int /*<<< orphan*/  nr_flags; int /*<<< orphan*/  nr_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_REG_ALL_NIC ; 
 int /*<<< orphan*/  NR_RX_RINGS_ONLY ; 
 int port_register (struct TestContext*) ; 

__attribute__((used)) static int
port_register_hwall_rx(struct TestContext *ctx)
{
	ctx->nr_mode = NR_REG_ALL_NIC;
	ctx->nr_flags |= NR_RX_RINGS_ONLY;
	return port_register(ctx);
}