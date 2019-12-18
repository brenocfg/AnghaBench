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
struct mem_ctl_info {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct mem_ctl_info* __find_mci_by_dev (struct device*) ; 
 int /*<<< orphan*/  mem_ctls_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct mem_ctl_info *find_mci_by_dev(struct device *dev)
{
	struct mem_ctl_info *ret;

	mutex_lock(&mem_ctls_mutex);
	ret = __find_mci_by_dev(dev);
	mutex_unlock(&mem_ctls_mutex);

	return ret;
}