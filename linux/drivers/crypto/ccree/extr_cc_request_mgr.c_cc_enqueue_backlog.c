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
struct device {int dummy; } ;
struct cc_req_mgr_handle {int /*<<< orphan*/  comptask; int /*<<< orphan*/  bl_lock; int /*<<< orphan*/  bl_len; int /*<<< orphan*/  backlog; } ;
struct cc_drvdata {struct cc_req_mgr_handle* request_mgr_handle; } ;
struct cc_bl_item {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct device* drvdata_to_dev (struct cc_drvdata*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cc_enqueue_backlog(struct cc_drvdata *drvdata,
			       struct cc_bl_item *bli)
{
	struct cc_req_mgr_handle *mgr = drvdata->request_mgr_handle;
	struct device *dev = drvdata_to_dev(drvdata);

	spin_lock_bh(&mgr->bl_lock);
	list_add_tail(&bli->list, &mgr->backlog);
	++mgr->bl_len;
	dev_dbg(dev, "+++bl len: %d\n", mgr->bl_len);
	spin_unlock_bh(&mgr->bl_lock);
	tasklet_schedule(&mgr->comptask);
}