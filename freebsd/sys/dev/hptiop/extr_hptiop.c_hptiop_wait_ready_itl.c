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
typedef  int u_int32_t ;
struct hpt_iop_hba {int dummy; } ;

/* Variables and functions */
 int BUS_SPACE_RD4_ITL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_SPACE_WRT4_ITL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int IOPMU_QUEUE_EMPTY ; 
 int /*<<< orphan*/  inbound_queue ; 
 int /*<<< orphan*/  outbound_intstatus ; 
 int /*<<< orphan*/  outbound_queue ; 

__attribute__((used)) static int hptiop_wait_ready_itl(struct hpt_iop_hba * hba, u_int32_t millisec)
{
	u_int32_t req=0;
	int i;

	for (i = 0; i < millisec; i++) {
		req = BUS_SPACE_RD4_ITL(inbound_queue);
		if (req != IOPMU_QUEUE_EMPTY)
			break;
		DELAY(1000);
	}

	if (req!=IOPMU_QUEUE_EMPTY) {
		BUS_SPACE_WRT4_ITL(outbound_queue, req);
		BUS_SPACE_RD4_ITL(outbound_intstatus);
		return 0;
	}

	return -1;
}