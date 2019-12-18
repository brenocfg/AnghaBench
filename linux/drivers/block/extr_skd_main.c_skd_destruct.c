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
struct skd_device {TYPE_1__* pdev; int /*<<< orphan*/  msgbuf_cache; int /*<<< orphan*/  sglist_cache; int /*<<< orphan*/  databuf_cache; int /*<<< orphan*/  start_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (struct skd_device*) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skd_free_disk (struct skd_device*) ; 
 int /*<<< orphan*/  skd_free_skcomp (struct skd_device*) ; 
 int /*<<< orphan*/  skd_free_skmsg (struct skd_device*) ; 
 int /*<<< orphan*/  skd_free_sksb (struct skd_device*) ; 

__attribute__((used)) static void skd_destruct(struct skd_device *skdev)
{
	if (skdev == NULL)
		return;

	cancel_work_sync(&skdev->start_queue);

	dev_dbg(&skdev->pdev->dev, "disk\n");
	skd_free_disk(skdev);

	dev_dbg(&skdev->pdev->dev, "sksb\n");
	skd_free_sksb(skdev);

	dev_dbg(&skdev->pdev->dev, "skmsg\n");
	skd_free_skmsg(skdev);

	dev_dbg(&skdev->pdev->dev, "skcomp\n");
	skd_free_skcomp(skdev);

	kmem_cache_destroy(skdev->databuf_cache);
	kmem_cache_destroy(skdev->sglist_cache);
	kmem_cache_destroy(skdev->msgbuf_cache);

	dev_dbg(&skdev->pdev->dev, "skdev\n");
	kfree(skdev);
}