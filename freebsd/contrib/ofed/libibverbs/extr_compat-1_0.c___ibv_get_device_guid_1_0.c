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
struct ibv_device_1_0 {int /*<<< orphan*/  real_device; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  ibv_get_device_guid (int /*<<< orphan*/ ) ; 

__be64 __ibv_get_device_guid_1_0(struct ibv_device_1_0 *device)
{
	return ibv_get_device_guid(device->real_device);
}