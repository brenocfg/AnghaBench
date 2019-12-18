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
struct skd_device {struct fit_comp_error_info* skerr_table; struct fit_completion_entry_v1* skcomp_table; int /*<<< orphan*/  cq_dma_address; TYPE_1__* pdev; } ;
struct fit_completion_entry_v1 {int dummy; } ;
struct fit_comp_error_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SKD_N_COMPLETION_ENTRY ; 
 int /*<<< orphan*/  SKD_SKCOMP_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 struct fit_completion_entry_v1* dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skd_cons_skcomp(struct skd_device *skdev)
{
	int rc = 0;
	struct fit_completion_entry_v1 *skcomp;

	dev_dbg(&skdev->pdev->dev,
		"comp pci_alloc, total bytes %zd entries %d\n",
		SKD_SKCOMP_SIZE, SKD_N_COMPLETION_ENTRY);

	skcomp = dma_alloc_coherent(&skdev->pdev->dev, SKD_SKCOMP_SIZE,
				    &skdev->cq_dma_address, GFP_KERNEL);

	if (skcomp == NULL) {
		rc = -ENOMEM;
		goto err_out;
	}

	skdev->skcomp_table = skcomp;
	skdev->skerr_table = (struct fit_comp_error_info *)((char *)skcomp +
							   sizeof(*skcomp) *
							   SKD_N_COMPLETION_ENTRY);

err_out:
	return rc;
}