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
struct TestContext {int nr_flags; int nr_tx_rings; int nr_rx_rings; } ;

/* Variables and functions */
 int NR_RX_RINGS_ONLY ; 
 int NR_TX_RINGS_ONLY ; 

__attribute__((used)) static int
num_registered_rings(struct TestContext *ctx)
{
	if (ctx->nr_flags & NR_TX_RINGS_ONLY) {
		return ctx->nr_tx_rings;
	}
	if (ctx->nr_flags & NR_RX_RINGS_ONLY) {
		return ctx->nr_rx_rings;
	}

	return ctx->nr_tx_rings + ctx->nr_rx_rings;
}