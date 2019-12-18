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
struct ipmi_device_id {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct bmc_device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int bmc_get_device_id (int /*<<< orphan*/ *,struct bmc_device*,struct ipmi_device_id*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ipmi_version_major (struct ipmi_device_id*) ; 
 int ipmi_version_minor (struct ipmi_device_id*) ; 
 int snprintf (char*,int,char*,int,int) ; 
 struct bmc_device* to_bmc_device (struct device*) ; 

__attribute__((used)) static ssize_t ipmi_version_show(struct device *dev,
				 struct device_attribute *attr,
				 char *buf)
{
	struct bmc_device *bmc = to_bmc_device(dev);
	struct ipmi_device_id id;
	int rv;

	rv = bmc_get_device_id(NULL, bmc, &id, NULL, NULL);
	if (rv)
		return rv;

	return snprintf(buf, 20, "%u.%u\n",
			ipmi_version_major(&id),
			ipmi_version_minor(&id));
}