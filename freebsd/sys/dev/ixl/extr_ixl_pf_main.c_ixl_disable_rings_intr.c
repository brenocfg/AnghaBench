#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ixl_vsi {int num_rx_queues; struct ixl_rx_queue* rx_queues; struct i40e_hw* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  me; } ;
struct ixl_rx_queue {TYPE_1__ rxr; } ;
struct i40e_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ixl_disable_queue (struct i40e_hw*,int /*<<< orphan*/ ) ; 

void
ixl_disable_rings_intr(struct ixl_vsi *vsi)
{
	struct i40e_hw		*hw = vsi->hw;
	struct ixl_rx_queue	*que = vsi->rx_queues;

	for (int i = 0; i < vsi->num_rx_queues; i++, que++)
		ixl_disable_queue(hw, que->rxr.me);
}