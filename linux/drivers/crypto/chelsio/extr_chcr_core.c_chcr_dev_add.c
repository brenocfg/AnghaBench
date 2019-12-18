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
struct chcr_dev {int /*<<< orphan*/  inflight; int /*<<< orphan*/  state; } ;
struct uld_ctx {int /*<<< orphan*/  entry; struct chcr_dev dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  drv_mutex; struct uld_ctx* last_dev; int /*<<< orphan*/  act_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHCR_ATTACH ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ drv_data ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void chcr_dev_add(struct uld_ctx *u_ctx)
{
	struct chcr_dev *dev;

	dev = &u_ctx->dev;
	dev->state = CHCR_ATTACH;
	atomic_set(&dev->inflight, 0);
	mutex_lock(&drv_data.drv_mutex);
	list_move(&u_ctx->entry, &drv_data.act_dev);
	if (!drv_data.last_dev)
		drv_data.last_dev = u_ctx;
	mutex_unlock(&drv_data.drv_mutex);
}