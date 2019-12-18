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
struct dca_provider {int /*<<< orphan*/  id; int /*<<< orphan*/ * cd; } ;

/* Variables and functions */
 int /*<<< orphan*/  dca_idr ; 
 int /*<<< orphan*/  dca_idr_lock ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void dca_sysfs_remove_provider(struct dca_provider *dca)
{
	device_unregister(dca->cd);
	dca->cd = NULL;
	spin_lock(&dca_idr_lock);
	idr_remove(&dca_idr, dca->id);
	spin_unlock(&dca_idr_lock);
}