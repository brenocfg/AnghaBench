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
struct chcr_dev {scalar_t__ state; int /*<<< orphan*/  detach_comp; int /*<<< orphan*/  detach_work; int /*<<< orphan*/  inflight; } ;
struct uld_ctx {struct chcr_dev dev; } ;

/* Variables and functions */
 scalar_t__ CHCR_DETACH ; 
 int /*<<< orphan*/  WQ_DETACH_TM ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chcr_dev_move (struct uld_ctx*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void chcr_detach_device(struct uld_ctx *u_ctx)
{
	struct chcr_dev *dev = &u_ctx->dev;

	if (dev->state == CHCR_DETACH) {
		pr_debug("Detached Event received for already detach device\n");
		return;
	}
	dev->state = CHCR_DETACH;
	if (atomic_read(&dev->inflight) != 0) {
		schedule_delayed_work(&dev->detach_work, WQ_DETACH_TM);
		wait_for_completion(&dev->detach_comp);
	}

	// Move u_ctx to inactive_dev list
	chcr_dev_move(u_ctx);
}