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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct counter_ext_unit {struct counter_device_ext* ext; } ;
struct counter_device_ext {int /*<<< orphan*/  priv; int /*<<< orphan*/  (* write ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,size_t) ;} ;
struct counter_device_attr {struct counter_ext_unit* component; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,size_t) ; 
 struct counter_device_attr* to_counter_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t counter_device_ext_store(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t len)
{
	const struct counter_device_attr *const devattr = to_counter_attr(attr);
	const struct counter_ext_unit *const component = devattr->component;
	const struct counter_device_ext *const ext = component->ext;

	return ext->write(dev_get_drvdata(dev), ext->priv, buf, len);
}