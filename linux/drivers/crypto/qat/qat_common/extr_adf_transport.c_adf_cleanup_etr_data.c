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
struct adf_etr_data {struct adf_etr_data* banks; int /*<<< orphan*/  debug; } ;
struct adf_accel_dev {struct adf_etr_data* transport; } ;

/* Variables and functions */
 int /*<<< orphan*/  adf_cleanup_etr_handles (struct adf_accel_dev*) ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct adf_etr_data*) ; 

void adf_cleanup_etr_data(struct adf_accel_dev *accel_dev)
{
	struct adf_etr_data *etr_data = accel_dev->transport;

	if (etr_data) {
		adf_cleanup_etr_handles(accel_dev);
		debugfs_remove(etr_data->debug);
		kfree(etr_data->banks);
		kfree(etr_data);
		accel_dev->transport = NULL;
	}
}