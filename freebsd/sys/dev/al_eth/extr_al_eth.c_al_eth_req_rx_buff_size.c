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
struct al_eth_adapter {int max_rx_buff_alloc_size; int /*<<< orphan*/  rx_mbuf_sz; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCLBYTES ; 
 int /*<<< orphan*/  MJUM16BYTES ; 
 int /*<<< orphan*/  MJUM9BYTES ; 
 int /*<<< orphan*/  MJUMPAGESIZE ; 

__attribute__((used)) static void
al_eth_req_rx_buff_size(struct al_eth_adapter *adapter, int size)
{

	/*
	* Determine the correct mbuf pool
	* for doing jumbo frames
	* Try from the smallest up to maximum supported
	*/
	adapter->rx_mbuf_sz = MCLBYTES;
	if (size > 2048) {
		if (adapter->max_rx_buff_alloc_size > 2048)
			adapter->rx_mbuf_sz = MJUMPAGESIZE;
		else
			return;
	}
	if (size > 4096) {
		if (adapter->max_rx_buff_alloc_size > 4096)
			adapter->rx_mbuf_sz = MJUM9BYTES;
		else
			return;
	}
	if (size > 9216) {
		if (adapter->max_rx_buff_alloc_size > 9216)
			adapter->rx_mbuf_sz = MJUM16BYTES;
		else
			return;
	}
}