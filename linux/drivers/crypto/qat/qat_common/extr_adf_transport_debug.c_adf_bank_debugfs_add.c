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
struct dentry {int dummy; } ;
struct adf_etr_bank_data {int bank_number; int /*<<< orphan*/  bank_debug_dir; int /*<<< orphan*/  bank_debug_cfg; struct adf_accel_dev* accel_dev; } ;
struct adf_accel_dev {TYPE_1__* transport; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_2__ {struct dentry* debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IRUSR ; 
 int /*<<< orphan*/  adf_bank_debug_fops ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct adf_etr_bank_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

int adf_bank_debugfs_add(struct adf_etr_bank_data *bank)
{
	struct adf_accel_dev *accel_dev = bank->accel_dev;
	struct dentry *parent = accel_dev->transport->debug;
	char name[8];

	snprintf(name, sizeof(name), "bank_%02d", bank->bank_number);
	bank->bank_debug_dir = debugfs_create_dir(name, parent);
	bank->bank_debug_cfg = debugfs_create_file("config", S_IRUSR,
						   bank->bank_debug_dir, bank,
						   &adf_bank_debug_fops);
	return 0;
}