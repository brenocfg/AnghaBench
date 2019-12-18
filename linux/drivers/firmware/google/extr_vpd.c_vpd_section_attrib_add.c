#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct vpd_section {int /*<<< orphan*/  attribs; int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {int mode; struct vpd_attrib_info* name; } ;
struct TYPE_5__ {struct vpd_attrib_info* private; int /*<<< orphan*/  read; int /*<<< orphan*/  size; TYPE_1__ attr; } ;
struct vpd_attrib_info {struct vpd_attrib_info* key; int /*<<< orphan*/  list; TYPE_2__ bin_attr; int /*<<< orphan*/  const* value; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ VPD_OK ; 
 int /*<<< orphan*/  kfree (struct vpd_attrib_info*) ; 
 struct vpd_attrib_info* kstrndup (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vpd_attrib_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_bin_attr_init (TYPE_2__*) ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  vpd_attrib_read ; 
 scalar_t__ vpd_section_check_key_name (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpd_section_attrib_add(const u8 *key, u32 key_len,
				  const u8 *value, u32 value_len,
				  void *arg)
{
	int ret;
	struct vpd_section *sec = arg;
	struct vpd_attrib_info *info;

	/*
	 * Return VPD_OK immediately to decode next entry if the current key
	 * name contains invalid characters.
	 */
	if (vpd_section_check_key_name(key, key_len) != VPD_OK)
		return VPD_OK;

	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->key = kstrndup(key, key_len, GFP_KERNEL);
	if (!info->key) {
		ret = -ENOMEM;
		goto free_info;
	}

	sysfs_bin_attr_init(&info->bin_attr);
	info->bin_attr.attr.name = info->key;
	info->bin_attr.attr.mode = 0444;
	info->bin_attr.size = value_len;
	info->bin_attr.read = vpd_attrib_read;
	info->bin_attr.private = info;

	info->value = value;

	INIT_LIST_HEAD(&info->list);

	ret = sysfs_create_bin_file(sec->kobj, &info->bin_attr);
	if (ret)
		goto free_info_key;

	list_add_tail(&info->list, &sec->attribs);
	return 0;

free_info_key:
	kfree(info->key);
free_info:
	kfree(info);

	return ret;
}