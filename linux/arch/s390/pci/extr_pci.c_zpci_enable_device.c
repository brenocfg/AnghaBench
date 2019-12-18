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
struct zpci_dev {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZPCI_FN_STATE_ONLINE ; 
 int /*<<< orphan*/  ZPCI_NR_DMA_SPACES ; 
 int /*<<< orphan*/  clp_disable_fh (struct zpci_dev*) ; 
 int clp_enable_fh (struct zpci_dev*,int /*<<< orphan*/ ) ; 
 int zpci_dma_init_device (struct zpci_dev*) ; 

int zpci_enable_device(struct zpci_dev *zdev)
{
	int rc;

	rc = clp_enable_fh(zdev, ZPCI_NR_DMA_SPACES);
	if (rc)
		goto out;

	rc = zpci_dma_init_device(zdev);
	if (rc)
		goto out_dma;

	zdev->state = ZPCI_FN_STATE_ONLINE;
	return 0;

out_dma:
	clp_disable_fh(zdev);
out:
	return rc;
}