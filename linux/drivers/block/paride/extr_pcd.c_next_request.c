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
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  __blk_mq_end_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_cur_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_update_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pcd_busy ; 
 int /*<<< orphan*/  pcd_lock ; 
 int /*<<< orphan*/ * pcd_req ; 
 int /*<<< orphan*/  pcd_request () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void next_request(blk_status_t err)
{
	unsigned long saved_flags;

	spin_lock_irqsave(&pcd_lock, saved_flags);
	if (!blk_update_request(pcd_req, err, blk_rq_cur_bytes(pcd_req))) {
		__blk_mq_end_request(pcd_req, err);
		pcd_req = NULL;
	}
	pcd_busy = 0;
	pcd_request();
	spin_unlock_irqrestore(&pcd_lock, saved_flags);
}