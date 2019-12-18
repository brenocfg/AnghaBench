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
struct cc_fips_handle {int /*<<< orphan*/  tasklet; int /*<<< orphan*/  nb; } ;
struct cc_drvdata {scalar_t__ hw_rev; struct cc_fips_handle* fips_handle; } ;

/* Variables and functions */
 scalar_t__ CC_HW_REV_712 ; 
 int /*<<< orphan*/  atomic_notifier_chain_unregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fips_fail_notif_chain ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void cc_fips_fini(struct cc_drvdata *drvdata)
{
	struct cc_fips_handle *fips_h = drvdata->fips_handle;

	if (drvdata->hw_rev < CC_HW_REV_712 || !fips_h)
		return;

	atomic_notifier_chain_unregister(&fips_fail_notif_chain, &fips_h->nb);

	/* Kill tasklet */
	tasklet_kill(&fips_h->tasklet);
	drvdata->fips_handle = NULL;
}