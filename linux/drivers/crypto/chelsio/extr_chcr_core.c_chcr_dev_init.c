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
struct chcr_dev {int /*<<< orphan*/  inflight; int /*<<< orphan*/  wqretry; int /*<<< orphan*/  state; int /*<<< orphan*/  detach_comp; int /*<<< orphan*/  detach_work; int /*<<< orphan*/  lock_chcr_dev; } ;
struct uld_ctx {int /*<<< orphan*/  entry; struct chcr_dev dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  drv_mutex; struct uld_ctx* last_dev; int /*<<< orphan*/  inact_dev; int /*<<< orphan*/  dev_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHCR_INIT ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WQ_RETRY ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  detach_work_fn ; 
 TYPE_1__ drv_data ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void chcr_dev_init(struct uld_ctx *u_ctx)
{
	struct chcr_dev *dev;

	dev = &u_ctx->dev;
	spin_lock_init(&dev->lock_chcr_dev);
	INIT_DELAYED_WORK(&dev->detach_work, detach_work_fn);
	init_completion(&dev->detach_comp);
	dev->state = CHCR_INIT;
	dev->wqretry = WQ_RETRY;
	atomic_inc(&drv_data.dev_count);
	atomic_set(&dev->inflight, 0);
	mutex_lock(&drv_data.drv_mutex);
	list_add_tail(&u_ctx->entry, &drv_data.inact_dev);
	if (!drv_data.last_dev)
		drv_data.last_dev = u_ctx;
	mutex_unlock(&drv_data.drv_mutex);
}