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
typedef  int /*<<< orphan*/  u8 ;
struct ifla_vf_info {int dummy; } ;
struct ib_device {int (* get_vf_config ) (struct ib_device*,int,int /*<<< orphan*/ ,struct ifla_vf_info*) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int stub1 (struct ib_device*,int,int /*<<< orphan*/ ,struct ifla_vf_info*) ; 

int ib_get_vf_config(struct ib_device *device, int vf, u8 port,
		     struct ifla_vf_info *info)
{
	if (!device->get_vf_config)
		return -ENOSYS;

	return device->get_vf_config(device, vf, port, info);
}