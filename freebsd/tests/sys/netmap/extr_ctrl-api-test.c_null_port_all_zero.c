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
struct TestContext {int nr_mem_id; scalar_t__ nr_rx_slots; scalar_t__ nr_tx_slots; scalar_t__ nr_rx_rings; scalar_t__ nr_tx_rings; int /*<<< orphan*/  nr_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_REG_NULL ; 
 int port_register (struct TestContext*) ; 

__attribute__((used)) static int
null_port_all_zero(struct TestContext *ctx)
{
	int ret;

	ctx->nr_mem_id = 1;
	ctx->nr_mode = NR_REG_NULL;
	ctx->nr_tx_rings = 0;
	ctx->nr_rx_rings = 0;
	ctx->nr_tx_slots = 0;
	ctx->nr_rx_slots = 0;
	ret = port_register(ctx);
	if (ret != 0) {
		return ret;
	}
	return 0;
}