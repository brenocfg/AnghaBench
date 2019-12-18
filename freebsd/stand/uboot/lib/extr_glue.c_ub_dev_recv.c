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
 int /*<<< orphan*/  API_DEV_READ ; 
 int API_ENODEV ; 
 int API_ESYSC ; 
 int /*<<< orphan*/  dev_net_valid (int) ; 
 struct device_info* devices ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int*,struct device_info*,void*,int*,int*) ; 

int
ub_dev_recv(int handle, void *buf, int len, int *rlen)
{
	struct device_info *di;
	int err = 0, act_len;

	if (!dev_net_valid(handle))
		return (API_ENODEV);

	di = &devices[handle];
	if (!syscall(API_DEV_READ, &err, di, buf, &len, &act_len))
		return (API_ESYSC);

	if (!err)
		*rlen = act_len;

	return (err);
}