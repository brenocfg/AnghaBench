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
struct TYPE_2__ {int ddr_av_base; int /*<<< orphan*/  pool; int /*<<< orphan*/  alloc; } ;
struct mthca_dev {TYPE_1__ av_table; } ;
struct mthca_ah {int type; int avdma; int /*<<< orphan*/  av; } ;

/* Variables and functions */
#define  MTHCA_AH_KMALLOC 130 
#define  MTHCA_AH_ON_HCA 129 
#define  MTHCA_AH_PCI_POOL 128 
 int MTHCA_AV_SIZE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pci_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int mthca_destroy_ah(struct mthca_dev *dev, struct mthca_ah *ah)
{
	switch (ah->type) {
	case MTHCA_AH_ON_HCA:
		mthca_free(&dev->av_table.alloc,
			   (ah->avdma - dev->av_table.ddr_av_base) /
			   MTHCA_AV_SIZE);
		break;

	case MTHCA_AH_PCI_POOL:
		pci_pool_free(dev->av_table.pool, ah->av, ah->avdma);
		break;

	case MTHCA_AH_KMALLOC:
		kfree(ah->av);
		break;
	}

	return 0;
}