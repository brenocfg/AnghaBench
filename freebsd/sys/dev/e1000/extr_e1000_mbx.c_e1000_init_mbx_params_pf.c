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
struct TYPE_6__ {int /*<<< orphan*/  rsts; int /*<<< orphan*/  acks; int /*<<< orphan*/  reqs; int /*<<< orphan*/  msgs_rx; int /*<<< orphan*/  msgs_tx; } ;
struct TYPE_5__ {int /*<<< orphan*/  check_for_rst; int /*<<< orphan*/  check_for_ack; int /*<<< orphan*/  check_for_msg; int /*<<< orphan*/  write_posted; int /*<<< orphan*/  read_posted; int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct e1000_mbx_info {TYPE_3__ stats; TYPE_2__ ops; int /*<<< orphan*/  size; int /*<<< orphan*/  usec_delay; int /*<<< orphan*/  timeout; } ;
struct TYPE_4__ {int type; } ;
struct e1000_hw {TYPE_1__ mac; struct e1000_mbx_info mbx; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_VFMAILBOX_SIZE ; 
#define  e1000_82576 130 
 int /*<<< orphan*/  e1000_check_for_ack_pf ; 
 int /*<<< orphan*/  e1000_check_for_msg_pf ; 
 int /*<<< orphan*/  e1000_check_for_rst_pf ; 
#define  e1000_i350 129 
#define  e1000_i354 128 
 int /*<<< orphan*/  e1000_read_mbx_pf ; 
 int /*<<< orphan*/  e1000_read_posted_mbx ; 
 int /*<<< orphan*/  e1000_write_mbx_pf ; 
 int /*<<< orphan*/  e1000_write_posted_mbx ; 

s32 e1000_init_mbx_params_pf(struct e1000_hw *hw)
{
	struct e1000_mbx_info *mbx = &hw->mbx;

	switch (hw->mac.type) {
	case e1000_82576:
	case e1000_i350:
	case e1000_i354:
		mbx->timeout = 0;
		mbx->usec_delay = 0;

		mbx->size = E1000_VFMAILBOX_SIZE;

		mbx->ops.read = e1000_read_mbx_pf;
		mbx->ops.write = e1000_write_mbx_pf;
		mbx->ops.read_posted = e1000_read_posted_mbx;
		mbx->ops.write_posted = e1000_write_posted_mbx;
		mbx->ops.check_for_msg = e1000_check_for_msg_pf;
		mbx->ops.check_for_ack = e1000_check_for_ack_pf;
		mbx->ops.check_for_rst = e1000_check_for_rst_pf;

		mbx->stats.msgs_tx = 0;
		mbx->stats.msgs_rx = 0;
		mbx->stats.reqs = 0;
		mbx->stats.acks = 0;
		mbx->stats.rsts = 0;
		/* FALLTHROUGH */
	default:
		return E1000_SUCCESS;
	}
}