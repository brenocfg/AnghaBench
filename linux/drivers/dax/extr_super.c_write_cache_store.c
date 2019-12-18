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
struct dax_device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t ENXIO ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct dax_device* dax_get_by_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dax_write_cache (struct dax_device*,int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  put_dax (struct dax_device*) ; 
 int strtobool (char const*,int*) ; 

__attribute__((used)) static ssize_t write_cache_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t len)
{
	bool write_cache;
	int rc = strtobool(buf, &write_cache);
	struct dax_device *dax_dev = dax_get_by_host(dev_name(dev));

	WARN_ON_ONCE(!dax_dev);
	if (!dax_dev)
		return -ENXIO;

	if (rc)
		len = rc;
	else
		dax_write_cache(dax_dev, write_cache);

	put_dax(dax_dev);
	return len;
}