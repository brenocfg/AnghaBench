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
struct bmc_device {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  guid_t ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ UUID_STRING_LEN ; 
 int bmc_get_device_id (int /*<<< orphan*/ *,struct bmc_device*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int snprintf (char*,scalar_t__,char*,int /*<<< orphan*/ *) ; 
 struct bmc_device* to_bmc_device (struct device*) ; 

__attribute__((used)) static ssize_t guid_show(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	struct bmc_device *bmc = to_bmc_device(dev);
	bool guid_set;
	guid_t guid;
	int rv;

	rv = bmc_get_device_id(NULL, bmc, NULL, &guid_set, &guid);
	if (rv)
		return rv;
	if (!guid_set)
		return -ENOENT;

	return snprintf(buf, UUID_STRING_LEN + 1 + 1, "%pUl\n", &guid);
}