#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ bitmap; } ;
struct TYPE_4__ {int /*<<< orphan*/ * prev; } ;
struct fsl_msi {int virq; int feature; int /*<<< orphan*/  msi_regs; TYPE_1__ bitmap; struct fsl_msi** cascade_array; TYPE_2__ list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int FSL_PIC_IP_MASK ; 
 int FSL_PIC_IP_VMPIC ; 
 int NR_MSI_REG_MAX ; 
 int /*<<< orphan*/  free_irq (int,struct fsl_msi*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int) ; 
 int /*<<< orphan*/  kfree (struct fsl_msi*) ; 
 int /*<<< orphan*/  list_del (TYPE_2__*) ; 
 int /*<<< orphan*/  msi_bitmap_free (TYPE_1__*) ; 
 struct fsl_msi* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int fsl_of_msi_remove(struct platform_device *ofdev)
{
	struct fsl_msi *msi = platform_get_drvdata(ofdev);
	int virq, i;

	if (msi->list.prev != NULL)
		list_del(&msi->list);
	for (i = 0; i < NR_MSI_REG_MAX; i++) {
		if (msi->cascade_array[i]) {
			virq = msi->cascade_array[i]->virq;

			BUG_ON(!virq);

			free_irq(virq, msi->cascade_array[i]);
			kfree(msi->cascade_array[i]);
			irq_dispose_mapping(virq);
		}
	}
	if (msi->bitmap.bitmap)
		msi_bitmap_free(&msi->bitmap);
	if ((msi->feature & FSL_PIC_IP_MASK) != FSL_PIC_IP_VMPIC)
		iounmap(msi->msi_regs);
	kfree(msi);

	return 0;
}