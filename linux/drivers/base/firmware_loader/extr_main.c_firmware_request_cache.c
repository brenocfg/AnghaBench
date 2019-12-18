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
struct device {int dummy; } ;

/* Variables and functions */
 int fw_add_devm_name (struct device*,char const*) ; 
 int /*<<< orphan*/  fw_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int firmware_request_cache(struct device *device, const char *name)
{
	int ret;

	mutex_lock(&fw_lock);
	ret = fw_add_devm_name(device, name);
	mutex_unlock(&fw_lock);

	return ret;
}