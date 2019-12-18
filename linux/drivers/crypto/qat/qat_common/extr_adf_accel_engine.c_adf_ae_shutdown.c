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
struct adf_hw_device_data {int /*<<< orphan*/  fw_name; } ;
struct adf_fw_loader_data {int /*<<< orphan*/  fw_loader; } ;
struct adf_accel_dev {struct adf_fw_loader_data* fw_loader; struct adf_hw_device_data* hw_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct adf_fw_loader_data*) ; 
 int /*<<< orphan*/  qat_hal_deinit (int /*<<< orphan*/ ) ; 

int adf_ae_shutdown(struct adf_accel_dev *accel_dev)
{
	struct adf_fw_loader_data *loader_data = accel_dev->fw_loader;
	struct adf_hw_device_data *hw_device = accel_dev->hw_device;

	if (!hw_device->fw_name)
		return 0;

	qat_hal_deinit(loader_data->fw_loader);
	kfree(accel_dev->fw_loader);
	accel_dev->fw_loader = NULL;
	return 0;
}