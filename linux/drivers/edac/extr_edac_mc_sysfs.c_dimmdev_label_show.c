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
struct dimm_info {char* label; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 struct dimm_info* to_dimm (struct device*) ; 

__attribute__((used)) static ssize_t dimmdev_label_show(struct device *dev,
				  struct device_attribute *mattr, char *data)
{
	struct dimm_info *dimm = to_dimm(dev);

	/* if field has not been initialized, there is nothing to send */
	if (!dimm->label[0])
		return 0;

	return snprintf(data, sizeof(dimm->label) + 1, "%s\n", dimm->label);
}