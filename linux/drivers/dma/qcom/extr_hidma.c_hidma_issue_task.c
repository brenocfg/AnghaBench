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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct hidma_dev {int /*<<< orphan*/  lldev; TYPE_1__ ddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hidma_ll_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hidma_issue_task(unsigned long arg)
{
	struct hidma_dev *dmadev = (struct hidma_dev *)arg;

	pm_runtime_get_sync(dmadev->ddev.dev);
	hidma_ll_start(dmadev->lldev);
}