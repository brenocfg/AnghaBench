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
typedef  int /*<<< orphan*/  umode_t ;
struct kobject {int dummy; } ;
struct device {int dummy; } ;
struct attribute {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  FME_FEATURE_ID_GLOBAL_ERR ; 
 int /*<<< orphan*/  dfl_get_feature_by_id (struct device*,int /*<<< orphan*/ ) ; 
 struct device* kobj_to_dev (struct kobject*) ; 

__attribute__((used)) static umode_t fme_global_err_attrs_visible(struct kobject *kobj,
					    struct attribute *attr, int n)
{
	struct device *dev = kobj_to_dev(kobj);

	/*
	 * sysfs entries are visible only if related private feature is
	 * enumerated.
	 */
	if (!dfl_get_feature_by_id(dev, FME_FEATURE_ID_GLOBAL_ERR))
		return 0;

	return attr->mode;
}