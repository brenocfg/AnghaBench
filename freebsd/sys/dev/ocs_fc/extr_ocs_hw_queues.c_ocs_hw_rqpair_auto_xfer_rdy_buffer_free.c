#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/ * auto_xfer_rdy_buf_pool; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  os; } ;
typedef  TYPE_2__ ocs_hw_t ;
struct TYPE_6__ {int /*<<< orphan*/  dma; } ;
struct TYPE_8__ {TYPE_1__ payload; } ;
typedef  TYPE_3__ ocs_hw_auto_xfer_rdy_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_dma_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_pool_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ocs_pool_get_count (int /*<<< orphan*/ *) ; 
 TYPE_3__* ocs_pool_get_instance (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ocs_hw_rqpair_auto_xfer_rdy_buffer_free(ocs_hw_t *hw)
{
	ocs_hw_auto_xfer_rdy_buffer_t *buf;
	uint32_t i;

	if (hw->auto_xfer_rdy_buf_pool != NULL) {
		ocs_lock(&hw->io_lock);
			for (i = 0; i < ocs_pool_get_count(hw->auto_xfer_rdy_buf_pool); i++) {
				buf = ocs_pool_get_instance(hw->auto_xfer_rdy_buf_pool, i);
				if (buf != NULL) {
					ocs_dma_free(hw->os, &buf->payload.dma);
				}
			}
		ocs_unlock(&hw->io_lock);

		ocs_pool_free(hw->auto_xfer_rdy_buf_pool);
		hw->auto_xfer_rdy_buf_pool = NULL;
	}
}