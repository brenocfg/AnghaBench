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
struct adf_accel_dev {int /*<<< orphan*/  accel_pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  adf_cleanup_bh (struct adf_accel_dev*) ; 
 int /*<<< orphan*/  adf_disable_msix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adf_free_irqs (struct adf_accel_dev*) ; 
 int /*<<< orphan*/  adf_isr_free_msix_entry_table (struct adf_accel_dev*) ; 

void adf_isr_resource_free(struct adf_accel_dev *accel_dev)
{
	adf_free_irqs(accel_dev);
	adf_cleanup_bh(accel_dev);
	adf_disable_msix(&accel_dev->accel_pci_dev);
	adf_isr_free_msix_entry_table(accel_dev);
}