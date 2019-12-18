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
typedef  int umode_t ;
struct dentry {int dummy; } ;
struct acpi_ec {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  global_lock; int /*<<< orphan*/  gpe; } ;

/* Variables and functions */
 int /*<<< orphan*/ * acpi_ec_debugfs_dir ; 
 int /*<<< orphan*/  acpi_ec_io_ops ; 
 int /*<<< orphan*/  debugfs_create_bool (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 void* debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct acpi_ec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_x32 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 TYPE_1__* first_ec ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 scalar_t__ write_support ; 

__attribute__((used)) static void acpi_ec_add_debugfs(struct acpi_ec *ec, unsigned int ec_device_count)
{
	struct dentry *dev_dir;
	char name[64];
	umode_t mode = 0400;

	if (ec_device_count == 0)
		acpi_ec_debugfs_dir = debugfs_create_dir("ec", NULL);

	sprintf(name, "ec%u", ec_device_count);
	dev_dir = debugfs_create_dir(name, acpi_ec_debugfs_dir);

	debugfs_create_x32("gpe", 0444, dev_dir, &first_ec->gpe);
	debugfs_create_bool("use_global_lock", 0444, dev_dir,
			    &first_ec->global_lock);

	if (write_support)
		mode = 0600;
	debugfs_create_file("io", mode, dev_dir, ec, &acpi_ec_io_ops);
}