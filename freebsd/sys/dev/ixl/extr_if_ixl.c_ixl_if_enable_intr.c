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
struct ixl_pf {struct ixl_vsi vsi; } ;
struct i40e_hw {int dummy; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 struct ixl_pf* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_enable_intr0 (struct i40e_hw*) ; 
 int /*<<< orphan*/  ixl_enable_queue (struct i40e_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixl_if_enable_intr(if_ctx_t ctx)
{
	struct ixl_pf *pf = iflib_get_softc(ctx);
	struct ixl_vsi *vsi = &pf->vsi;
	struct i40e_hw		*hw = vsi->hw;
	struct ixl_rx_queue	*que = vsi->rx_queues;

	ixl_enable_intr0(hw);
	/* Enable queue interrupts */
	for (int i = 0; i < vsi->num_rx_queues; i++, que++)
		/* TODO: Queue index parameter is probably wrong */
		ixl_enable_queue(hw, que->rxr.me);
}