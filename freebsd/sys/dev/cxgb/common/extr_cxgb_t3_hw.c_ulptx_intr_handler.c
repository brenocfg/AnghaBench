#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct intr_info {int member_0; char* member_1; int member_2; int member_3; } ;
struct TYPE_5__ {int /*<<< orphan*/  irq_stats; } ;
typedef  TYPE_1__ adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_ULPTX_INT_CAUSE ; 
#define  F_PBL_BOUND_ERR_CH0 131 
#define  F_PBL_BOUND_ERR_CH1 130 
#define  STAT_ULP_CH0_PBL_OOB 129 
#define  STAT_ULP_CH1_PBL_OOB 128 
 int /*<<< orphan*/  t3_fatal_err (TYPE_1__*) ; 
 scalar_t__ t3_handle_intr_status (TYPE_1__*,int /*<<< orphan*/ ,int,struct intr_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ulptx_intr_handler(adapter_t *adapter)
{
	static struct intr_info ulptx_intr_info[] = {
		{ F_PBL_BOUND_ERR_CH0, "ULP TX channel 0 PBL out of bounds",
		  STAT_ULP_CH0_PBL_OOB, 0 },
		{ F_PBL_BOUND_ERR_CH1, "ULP TX channel 1 PBL out of bounds",
		  STAT_ULP_CH1_PBL_OOB, 0 },
		{ 0xfc, "ULP TX parity error", -1, 1 },
		{ 0 }
        };

	if (t3_handle_intr_status(adapter, A_ULPTX_INT_CAUSE, 0xffffffff,
				  ulptx_intr_info, adapter->irq_stats))
		t3_fatal_err(adapter);
}