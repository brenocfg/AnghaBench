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
struct mem_ctl_info {int /*<<< orphan*/  pdev; } ;
struct ghes {int dummy; } ;
struct TYPE_2__ {struct mem_ctl_info* mci; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_mc_del_mc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_mc_free (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  ghes_init ; 
 TYPE_1__* ghes_pvt ; 

void ghes_edac_unregister(struct ghes *ghes)
{
	struct mem_ctl_info *mci;

	if (!ghes_pvt)
		return;

	if (atomic_dec_return(&ghes_init))
		return;

	mci = ghes_pvt->mci;
	ghes_pvt = NULL;
	edac_mc_del_mc(mci->pdev);
	edac_mc_free(mci);
}