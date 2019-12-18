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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ BCOM_INITIATOR_ALWAYS ; 
 scalar_t__ bcom_desc_initiator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcom_desc_is_drd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcom_drd_is_extended (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcom_set_desc_initiator (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bcom_set_tcr_initiator (int,int) ; 
 int /*<<< orphan*/ * bcom_task_desc (int) ; 
 int bcom_task_num_descs (int) ; 

void
bcom_set_initiator(int task, int initiator)
{
	int i;
	int num_descs;
	u32 *desc;
	int next_drd_has_initiator;

	bcom_set_tcr_initiator(task, initiator);

	/* Just setting tcr is apparently not enough due to some problem */
	/* with it. So we just go thru all the microcode and replace in  */
	/* the DRD directly */

	desc = bcom_task_desc(task);
	next_drd_has_initiator = 1;
	num_descs = bcom_task_num_descs(task);

	for (i=0; i<num_descs; i++, desc++) {
		if (!bcom_desc_is_drd(*desc))
			continue;
		if (next_drd_has_initiator)
			if (bcom_desc_initiator(*desc) != BCOM_INITIATOR_ALWAYS)
				bcom_set_desc_initiator(desc, initiator);
		next_drd_has_initiator = !bcom_drd_is_extended(*desc);
	}
}