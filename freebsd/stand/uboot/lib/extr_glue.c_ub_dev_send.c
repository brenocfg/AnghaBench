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
struct device_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  API_DEV_WRITE ; 
 int API_ENODEV ; 
 int API_ESYSC ; 
 int /*<<< orphan*/  dev_net_valid (int) ; 
 struct device_info* devices ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int*,struct device_info*,void*,int*) ; 

int
ub_dev_send(int handle, void *buf, int len)
{
	struct device_info *di;
	int err = 0;

	if (!dev_net_valid(handle))
		return (API_ENODEV);

	di = &devices[handle];
	if (!syscall(API_DEV_WRITE, &err, di, buf, &len))
		return (API_ESYSC);

	return (err);
}