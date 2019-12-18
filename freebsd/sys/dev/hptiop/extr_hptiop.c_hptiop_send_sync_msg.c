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
typedef  scalar_t__ u_int32_t ;
struct hpt_iop_hba {scalar_t__ msg_done; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* iop_intr ) (struct hpt_iop_hba*) ;int /*<<< orphan*/  (* post_msg ) (struct hpt_iop_hba*,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  stub1 (struct hpt_iop_hba*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct hpt_iop_hba*) ; 

__attribute__((used)) static int hptiop_send_sync_msg(struct hpt_iop_hba *hba,
					u_int32_t msg, u_int32_t millisec)
{
	u_int32_t i;

	hba->msg_done = 0;
	hba->ops->post_msg(hba, msg);

	for (i=0; i<millisec; i++) {
		hba->ops->iop_intr(hba);
		if (hba->msg_done)
			break;
		DELAY(1000);
	}

	return hba->msg_done? 0 : -1;
}