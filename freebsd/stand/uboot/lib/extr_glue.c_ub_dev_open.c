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
 int /*<<< orphan*/  API_DEV_OPEN ; 
 int API_EINVAL ; 
 int UB_MAX_DEV ; 
 struct device_info* devices ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int*,struct device_info*) ; 

int
ub_dev_open(int handle)
{
	struct device_info *di;
	int err = 0;

	if (handle < 0 || handle >= UB_MAX_DEV)
		return (API_EINVAL);

	di = &devices[handle];
	if (!syscall(API_DEV_OPEN, &err, di))
		return (-1);

	return (err);
}