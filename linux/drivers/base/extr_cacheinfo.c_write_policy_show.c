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
struct cacheinfo {unsigned int attributes; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned int CACHE_WRITE_BACK ; 
 unsigned int CACHE_WRITE_THROUGH ; 
 struct cacheinfo* dev_get_drvdata (struct device*) ; 
 int sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t write_policy_show(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	struct cacheinfo *this_leaf = dev_get_drvdata(dev);
	unsigned int ci_attr = this_leaf->attributes;
	int n = 0;

	if (ci_attr & CACHE_WRITE_THROUGH)
		n = sprintf(buf, "WriteThrough\n");
	else if (ci_attr & CACHE_WRITE_BACK)
		n = sprintf(buf, "WriteBack\n");
	return n;
}