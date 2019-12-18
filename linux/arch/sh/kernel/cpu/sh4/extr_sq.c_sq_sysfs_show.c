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
struct sq_sysfs_attr {int /*<<< orphan*/  (* show ) (char*) ;} ;
struct kobject {int dummy; } ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ likely (int /*<<< orphan*/  (*) (char*)) ; 
 int /*<<< orphan*/  stub1 (char*) ; 
 struct sq_sysfs_attr* to_sq_sysfs_attr (struct attribute*) ; 

__attribute__((used)) static ssize_t sq_sysfs_show(struct kobject *kobj, struct attribute *attr,
			     char *buf)
{
	struct sq_sysfs_attr *sattr = to_sq_sysfs_attr(attr);

	if (likely(sattr->show))
		return sattr->show(buf);

	return -EIO;
}