#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int __efivar_entry_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efivar_sysfs_destroy ; 
 int /*<<< orphan*/  efivar_sysfs_list ; 
 scalar_t__ efivars_del_var ; 
 TYPE_1__* efivars_kset ; 
 scalar_t__ efivars_new_var ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  kset_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void efivars_sysfs_exit(void)
{
	/* Remove all entries and destroy */
	int err;

	err = __efivar_entry_iter(efivar_sysfs_destroy, &efivar_sysfs_list,
				  NULL, NULL);
	if (err) {
		pr_err("efivars: Failed to destroy sysfs entries\n");
		return;
	}

	if (efivars_new_var)
		sysfs_remove_bin_file(&efivars_kset->kobj, efivars_new_var);
	if (efivars_del_var)
		sysfs_remove_bin_file(&efivars_kset->kobj, efivars_del_var);
	kfree(efivars_new_var);
	kfree(efivars_del_var);
	kset_unregister(efivars_kset);
}