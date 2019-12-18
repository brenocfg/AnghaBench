#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ rsts; scalar_t__ acks; scalar_t__ reqs; scalar_t__ msgs_rx; scalar_t__ msgs_tx; } ;
struct TYPE_5__ {int /*<<< orphan*/  check_for_rst; int /*<<< orphan*/  check_for_ack; int /*<<< orphan*/  check_for_msg; int /*<<< orphan*/  write_posted; int /*<<< orphan*/  read_posted; int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct ixgbe_mbx_info {TYPE_3__ stats; TYPE_2__ ops; int /*<<< orphan*/  size; scalar_t__ usec_delay; scalar_t__ timeout; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_1__ mac; struct ixgbe_mbx_info mbx; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_VFMAILBOX_SIZE ; 
 int /*<<< orphan*/  ixgbe_check_for_ack_pf ; 
 int /*<<< orphan*/  ixgbe_check_for_msg_pf ; 
 int /*<<< orphan*/  ixgbe_check_for_rst_pf ; 
 scalar_t__ ixgbe_mac_82599EB ; 
 scalar_t__ ixgbe_mac_X540 ; 
 scalar_t__ ixgbe_mac_X550 ; 
 scalar_t__ ixgbe_mac_X550EM_a ; 
 scalar_t__ ixgbe_mac_X550EM_x ; 
 int /*<<< orphan*/  ixgbe_read_mbx_pf ; 
 int /*<<< orphan*/  ixgbe_read_posted_mbx ; 
 int /*<<< orphan*/  ixgbe_write_mbx_pf ; 
 int /*<<< orphan*/  ixgbe_write_posted_mbx ; 

void ixgbe_init_mbx_params_pf(struct ixgbe_hw *hw)
{
	struct ixgbe_mbx_info *mbx = &hw->mbx;

	if (hw->mac.type != ixgbe_mac_82599EB &&
	    hw->mac.type != ixgbe_mac_X550 &&
	    hw->mac.type != ixgbe_mac_X550EM_x &&
	    hw->mac.type != ixgbe_mac_X550EM_a &&
	    hw->mac.type != ixgbe_mac_X540)
		return;

	mbx->timeout = 0;
	mbx->usec_delay = 0;

	mbx->size = IXGBE_VFMAILBOX_SIZE;

	mbx->ops.read = ixgbe_read_mbx_pf;
	mbx->ops.write = ixgbe_write_mbx_pf;
	mbx->ops.read_posted = ixgbe_read_posted_mbx;
	mbx->ops.write_posted = ixgbe_write_posted_mbx;
	mbx->ops.check_for_msg = ixgbe_check_for_msg_pf;
	mbx->ops.check_for_ack = ixgbe_check_for_ack_pf;
	mbx->ops.check_for_rst = ixgbe_check_for_rst_pf;

	mbx->stats.msgs_tx = 0;
	mbx->stats.msgs_rx = 0;
	mbx->stats.reqs = 0;
	mbx->stats.acks = 0;
	mbx->stats.rsts = 0;
}