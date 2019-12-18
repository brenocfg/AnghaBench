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
struct xgbe_desc_if {int /*<<< orphan*/  wrapper_rx_desc_init; int /*<<< orphan*/  wrapper_tx_desc_init; int /*<<< orphan*/  unmap_rdata; int /*<<< orphan*/  map_rx_buffer; int /*<<< orphan*/  map_tx_skb; int /*<<< orphan*/  free_ring_resources; int /*<<< orphan*/  alloc_ring_resources; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*) ; 
 int /*<<< orphan*/  xgbe_alloc_ring_resources ; 
 int /*<<< orphan*/  xgbe_free_ring_resources ; 
 int /*<<< orphan*/  xgbe_map_rx_buffer ; 
 int /*<<< orphan*/  xgbe_map_tx_skb ; 
 int /*<<< orphan*/  xgbe_unmap_rdata ; 
 int /*<<< orphan*/  xgbe_wrapper_rx_descriptor_init ; 
 int /*<<< orphan*/  xgbe_wrapper_tx_descriptor_init ; 

void xgbe_init_function_ptrs_desc(struct xgbe_desc_if *desc_if)
{
	DBGPR("-->xgbe_init_function_ptrs_desc\n");

	desc_if->alloc_ring_resources = xgbe_alloc_ring_resources;
	desc_if->free_ring_resources = xgbe_free_ring_resources;
	desc_if->map_tx_skb = xgbe_map_tx_skb;
	desc_if->map_rx_buffer = xgbe_map_rx_buffer;
	desc_if->unmap_rdata = xgbe_unmap_rdata;
	desc_if->wrapper_tx_desc_init = xgbe_wrapper_tx_descriptor_init;
	desc_if->wrapper_rx_desc_init = xgbe_wrapper_rx_descriptor_init;

	DBGPR("<--xgbe_init_function_ptrs_desc\n");
}