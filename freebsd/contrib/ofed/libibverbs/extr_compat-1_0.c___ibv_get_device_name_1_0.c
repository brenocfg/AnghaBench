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

/* Variables and functions */
 char const* ibv_get_device_name (int /*<<< orphan*/ ) ; 

const char *__ibv_get_device_name_1_0(struct ibv_device_1_0 *device)
{
	return ibv_get_device_name(device->real_device);
}