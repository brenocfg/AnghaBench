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
typedef  int u32 ;
struct TYPE_4__ {int id; int /*<<< orphan*/  state; } ;
struct skd_special_context {TYPE_2__ req; } ;
struct skd_device {struct skd_special_context internal_skspcl; TYPE_1__* pdev; int /*<<< orphan*/  lock; } ;
struct fit_completion_entry_v1 {int tag; } ;
struct fit_comp_error_info {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  SKD_ID_FIT_MSG 130 
#define  SKD_ID_INTERNAL 129 
#define  SKD_ID_RW_REQUEST 128 
 int SKD_ID_SLOT_MASK ; 
 int SKD_ID_TABLE_MASK ; 
 int /*<<< orphan*/  SKD_REQ_STATE_BUSY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skd_complete_internal (struct skd_device*,struct fit_completion_entry_v1*,struct fit_comp_error_info*,struct skd_special_context*) ; 

__attribute__((used)) static void skd_complete_other(struct skd_device *skdev,
			       struct fit_completion_entry_v1 *skcomp,
			       struct fit_comp_error_info *skerr)
{
	u32 req_id = 0;
	u32 req_table;
	u32 req_slot;
	struct skd_special_context *skspcl;

	lockdep_assert_held(&skdev->lock);

	req_id = skcomp->tag;
	req_table = req_id & SKD_ID_TABLE_MASK;
	req_slot = req_id & SKD_ID_SLOT_MASK;

	dev_dbg(&skdev->pdev->dev, "table=0x%x id=0x%x slot=%d\n", req_table,
		req_id, req_slot);

	/*
	 * Based on the request id, determine how to dispatch this completion.
	 * This swich/case is finding the good cases and forwarding the
	 * completion entry. Errors are reported below the switch.
	 */
	switch (req_table) {
	case SKD_ID_RW_REQUEST:
		/*
		 * The caller, skd_isr_completion_posted() above,
		 * handles r/w requests. The only way we get here
		 * is if the req_slot is out of bounds.
		 */
		break;

	case SKD_ID_INTERNAL:
		if (req_slot == 0) {
			skspcl = &skdev->internal_skspcl;
			if (skspcl->req.id == req_id &&
			    skspcl->req.state == SKD_REQ_STATE_BUSY) {
				skd_complete_internal(skdev,
						      skcomp, skerr, skspcl);
				return;
			}
		}
		break;

	case SKD_ID_FIT_MSG:
		/*
		 * These id's should never appear in a completion record.
		 */
		break;

	default:
		/*
		 * These id's should never appear anywhere;
		 */
		break;
	}

	/*
	 * If we get here it is a bad or stale id.
	 */
}