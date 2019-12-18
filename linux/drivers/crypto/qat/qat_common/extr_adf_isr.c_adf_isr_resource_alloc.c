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
struct adf_accel_dev {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ adf_enable_msix (struct adf_accel_dev*) ; 
 int adf_isr_alloc_msix_entry_table (struct adf_accel_dev*) ; 
 int /*<<< orphan*/  adf_isr_resource_free (struct adf_accel_dev*) ; 
 scalar_t__ adf_request_irqs (struct adf_accel_dev*) ; 
 scalar_t__ adf_setup_bh (struct adf_accel_dev*) ; 

int adf_isr_resource_alloc(struct adf_accel_dev *accel_dev)
{
	int ret;

	ret = adf_isr_alloc_msix_entry_table(accel_dev);
	if (ret)
		return ret;
	if (adf_enable_msix(accel_dev))
		goto err_out;

	if (adf_setup_bh(accel_dev))
		goto err_out;

	if (adf_request_irqs(accel_dev))
		goto err_out;

	return 0;
err_out:
	adf_isr_resource_free(accel_dev);
	return -EFAULT;
}