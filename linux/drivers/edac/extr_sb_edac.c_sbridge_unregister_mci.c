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
struct sbridge_pvt {int dummy; } ;
struct sbridge_dev {struct mem_ctl_info* mci; TYPE_1__** pdev; } ;
struct mem_ctl_info {int /*<<< orphan*/ * ctl_name; int /*<<< orphan*/  pdev; struct sbridge_pvt* pvt_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  edac_dbg (int,char*,struct mem_ctl_info*,...) ; 
 int /*<<< orphan*/  edac_mc_del_mc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_mc_free (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbridge_printk (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void sbridge_unregister_mci(struct sbridge_dev *sbridge_dev)
{
	struct mem_ctl_info *mci = sbridge_dev->mci;
	struct sbridge_pvt *pvt;

	if (unlikely(!mci || !mci->pvt_info)) {
		edac_dbg(0, "MC: dev = %p\n", &sbridge_dev->pdev[0]->dev);

		sbridge_printk(KERN_ERR, "Couldn't find mci handler\n");
		return;
	}

	pvt = mci->pvt_info;

	edac_dbg(0, "MC: mci = %p, dev = %p\n",
		 mci, &sbridge_dev->pdev[0]->dev);

	/* Remove MC sysfs nodes */
	edac_mc_del_mc(mci->pdev);

	edac_dbg(1, "%s: free mci struct\n", mci->ctl_name);
	kfree(mci->ctl_name);
	edac_mc_free(mci);
	sbridge_dev->mci = NULL;
}