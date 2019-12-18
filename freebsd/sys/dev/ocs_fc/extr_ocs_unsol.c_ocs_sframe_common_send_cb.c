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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ocs_hw_t ;
struct TYPE_2__ {int /*<<< orphan*/  seq; int /*<<< orphan*/  wqcb; int /*<<< orphan*/ * hw; } ;
typedef  TYPE_1__ ocs_hw_send_frame_context_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_hw_reqtag_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_hw_sequence_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ocs_sframe_common_send_cb(void *arg, uint8_t *cqe, int32_t status)
{
	ocs_hw_send_frame_context_t *ctx = arg;
	ocs_hw_t *hw = ctx->hw;

	/* Free WQ completion callback */
	ocs_hw_reqtag_free(hw, ctx->wqcb);

	/* Free sequence */
	ocs_hw_sequence_free(hw, ctx->seq);
}