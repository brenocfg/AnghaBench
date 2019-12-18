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
struct fw_cfg_sysfs_entry {int /*<<< orphan*/  kobj; int /*<<< orphan*/  name; int /*<<< orphan*/  select; int /*<<< orphan*/  size; } ;
struct fw_cfg_file {int /*<<< orphan*/  name; int /*<<< orphan*/  select; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FW_CFG_MAX_FILE_PATH ; 
 int /*<<< orphan*/  FW_CFG_VMCOREINFO_FILENAME ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_cfg_build_symlink (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fw_cfg_dma_enabled () ; 
 int /*<<< orphan*/  fw_cfg_fname_kset ; 
 int /*<<< orphan*/  fw_cfg_sel_ko ; 
 int /*<<< orphan*/  fw_cfg_sysfs_attr_raw ; 
 int /*<<< orphan*/  fw_cfg_sysfs_cache_enlist (struct fw_cfg_sysfs_entry*) ; 
 int /*<<< orphan*/  fw_cfg_sysfs_entry_ktype ; 
 scalar_t__ fw_cfg_write_vmcoreinfo (struct fw_cfg_file const*) ; 
 int /*<<< orphan*/  is_kdump_kernel () ; 
 int /*<<< orphan*/  kfree (struct fw_cfg_sysfs_entry*) ; 
 int /*<<< orphan*/  kobject_del (int /*<<< orphan*/ *) ; 
 int kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct fw_cfg_sysfs_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fw_cfg_register_file(const struct fw_cfg_file *f)
{
	int err;
	struct fw_cfg_sysfs_entry *entry;

#ifdef CONFIG_CRASH_CORE
	if (fw_cfg_dma_enabled() &&
		strcmp(f->name, FW_CFG_VMCOREINFO_FILENAME) == 0 &&
		!is_kdump_kernel()) {
		if (fw_cfg_write_vmcoreinfo(f) < 0)
			pr_warn("fw_cfg: failed to write vmcoreinfo");
	}
#endif

	/* allocate new entry */
	entry = kzalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry)
		return -ENOMEM;

	/* set file entry information */
	entry->size = be32_to_cpu(f->size);
	entry->select = be16_to_cpu(f->select);
	memcpy(entry->name, f->name, FW_CFG_MAX_FILE_PATH);

	/* register entry under "/sys/firmware/qemu_fw_cfg/by_key/" */
	err = kobject_init_and_add(&entry->kobj, &fw_cfg_sysfs_entry_ktype,
				   fw_cfg_sel_ko, "%d", entry->select);
	if (err)
		goto err_register;

	/* add raw binary content access */
	err = sysfs_create_bin_file(&entry->kobj, &fw_cfg_sysfs_attr_raw);
	if (err)
		goto err_add_raw;

	/* try adding "/sys/firmware/qemu_fw_cfg/by_name/" symlink */
	fw_cfg_build_symlink(fw_cfg_fname_kset, &entry->kobj, entry->name);

	/* success, add entry to global cache */
	fw_cfg_sysfs_cache_enlist(entry);
	return 0;

err_add_raw:
	kobject_del(&entry->kobj);
err_register:
	kfree(entry);
	return err;
}