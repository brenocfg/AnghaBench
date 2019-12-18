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
struct devinfo_dev {int /*<<< orphan*/  dd_desc; int /*<<< orphan*/ * dd_location; int /*<<< orphan*/ * dd_name; } ;
struct device_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct device_entry* device_entry_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct device_entry *
device_entry_create_devinfo(const struct devinfo_dev *dev_p)
{

	assert(dev_p->dd_name != NULL);
	assert(dev_p->dd_location != NULL);

	return (device_entry_create(dev_p->dd_name, dev_p->dd_location,
	    dev_p->dd_desc));
}