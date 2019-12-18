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
struct dimm_info {size_t dtype; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char** dev_types ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct dimm_info* to_dimm (struct device*) ; 

__attribute__((used)) static ssize_t dimmdev_dev_type_show(struct device *dev,
				     struct device_attribute *mattr, char *data)
{
	struct dimm_info *dimm = to_dimm(dev);

	return sprintf(data, "%s\n", dev_types[dimm->dtype]);
}