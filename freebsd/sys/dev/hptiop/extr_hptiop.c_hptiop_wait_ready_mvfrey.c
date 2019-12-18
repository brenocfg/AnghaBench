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
typedef  int /*<<< orphan*/  u_int32_t ;
struct hpt_iop_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOPMU_INBOUND_MSG0_NOP ; 
 scalar_t__ hptiop_send_sync_msg (struct hpt_iop_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hptiop_wait_ready_mvfrey(struct hpt_iop_hba * hba,
							u_int32_t millisec)
{
	if (hptiop_send_sync_msg(hba, IOPMU_INBOUND_MSG0_NOP, millisec))
		return -1;

	return 0;
}