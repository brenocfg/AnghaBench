#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ count; int /*<<< orphan*/  bah; int /*<<< orphan*/  bal; int /*<<< orphan*/  len; int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;
struct TYPE_4__ {int /*<<< orphan*/  asq_spinlock; TYPE_1__ asq; } ;
struct i40e_hw {TYPE_2__ aq; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int I40E_ERR_NOT_READY ; 
 int I40E_SUCCESS ; 
 int /*<<< orphan*/  i40e_acquire_spinlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_free_asq_bufs (struct i40e_hw*) ; 
 int /*<<< orphan*/  i40e_release_spinlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_shutdown_asq(struct i40e_hw *hw)
{
	enum i40e_status_code ret_code = I40E_SUCCESS;

	i40e_acquire_spinlock(&hw->aq.asq_spinlock);

	if (hw->aq.asq.count == 0) {
		ret_code = I40E_ERR_NOT_READY;
		goto shutdown_asq_out;
	}

	/* Stop firmware AdminQ processing */
	wr32(hw, hw->aq.asq.head, 0);
	wr32(hw, hw->aq.asq.tail, 0);
	wr32(hw, hw->aq.asq.len, 0);
	wr32(hw, hw->aq.asq.bal, 0);
	wr32(hw, hw->aq.asq.bah, 0);

	hw->aq.asq.count = 0; /* to indicate uninitialized queue */

	/* free ring buffers */
	i40e_free_asq_bufs(hw);

shutdown_asq_out:
	i40e_release_spinlock(&hw->aq.asq_spinlock);
	return ret_code;
}