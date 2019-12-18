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
struct al_eth_ring {int cmpl_is_running; int /*<<< orphan*/  unmask_val; int /*<<< orphan*/  unmask_reg_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  al_data_memory_barrier () ; 
 int /*<<< orphan*/  al_eth_irq_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_eth_tx_do_cleanup (struct al_eth_ring*) ; 
 scalar_t__ napi ; 

__attribute__((used)) static void
al_eth_tx_cmpl_work(void *arg, int pending)
{
	struct al_eth_ring *tx_ring = arg;

	if (napi != 0) {
		tx_ring->cmpl_is_running = 1;
		al_data_memory_barrier();
	}

	al_eth_tx_do_cleanup(tx_ring);

	if (napi != 0) {
		tx_ring->cmpl_is_running = 0;
		al_data_memory_barrier();
	}
	/* all work done, enable IRQs */
	al_eth_irq_config(tx_ring->unmask_reg_offset, tx_ring->unmask_val);
}