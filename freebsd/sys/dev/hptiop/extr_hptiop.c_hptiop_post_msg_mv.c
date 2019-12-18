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
 int /*<<< orphan*/  BUS_SPACE_RD4_MV0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_SPACE_WRT4_MV0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_SPACE_WRT4_MV2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVIOP_MU_INBOUND_INT_MSG ; 
 int /*<<< orphan*/  inbound_doorbell ; 
 int /*<<< orphan*/  inbound_msg ; 
 int /*<<< orphan*/  outbound_intmask ; 

__attribute__((used)) static void hptiop_post_msg_mv(struct hpt_iop_hba *hba, u_int32_t msg)
{

	BUS_SPACE_WRT4_MV2(inbound_msg, msg);
	BUS_SPACE_WRT4_MV0(inbound_doorbell, MVIOP_MU_INBOUND_INT_MSG);

	BUS_SPACE_RD4_MV0(outbound_intmask);
}