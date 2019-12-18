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
struct drbd_request {int /*<<< orphan*/  device; int /*<<< orphan*/  tl_requests; } ;
struct TYPE_2__ {int /*<<< orphan*/  worker; int /*<<< orphan*/  wq; int /*<<< orphan*/  lock; int /*<<< orphan*/  writes; } ;

/* Variables and functions */
 int /*<<< orphan*/  dec_ap_bio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ retry ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void drbd_restart_request(struct drbd_request *req)
{
	unsigned long flags;
	spin_lock_irqsave(&retry.lock, flags);
	list_move_tail(&req->tl_requests, &retry.writes);
	spin_unlock_irqrestore(&retry.lock, flags);

	/* Drop the extra reference that would otherwise
	 * have been dropped by complete_master_bio.
	 * do_retry() needs to grab a new one. */
	dec_ap_bio(req->device);

	queue_work(retry.wq, &retry.worker);
}