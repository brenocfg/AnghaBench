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
struct ena_adapter {int /*<<< orphan*/ * rx_buf_tag; } ;

/* Variables and functions */
 int bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static int
ena_free_rx_dma_tag(struct ena_adapter *adapter)
{
	int ret;

	ret = bus_dma_tag_destroy(adapter->rx_buf_tag);

	if (likely(ret == 0))
		adapter->rx_buf_tag = NULL;

	return (ret);
}