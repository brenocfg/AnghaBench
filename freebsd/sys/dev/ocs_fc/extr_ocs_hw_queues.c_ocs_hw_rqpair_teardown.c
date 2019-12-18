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
typedef  int /*<<< orphan*/  ocs_hw_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_hw_rqpair_auto_xfer_rdy_buffer_free (int /*<<< orphan*/ *) ; 

void
ocs_hw_rqpair_teardown(ocs_hw_t *hw)
{
	/* We need to free any auto xfer ready buffers */
	ocs_hw_rqpair_auto_xfer_rdy_buffer_free(hw);
}