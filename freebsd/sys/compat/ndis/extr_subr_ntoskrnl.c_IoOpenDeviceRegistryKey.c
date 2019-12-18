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
typedef  int /*<<< orphan*/  uint32_t ;
struct device_object {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  NDIS_STATUS_INVALID_DEVICE_REQUEST ; 

__attribute__((used)) static int32_t
IoOpenDeviceRegistryKey(struct device_object *devobj, uint32_t type,
    uint32_t mask, void **key)
{
	return (NDIS_STATUS_INVALID_DEVICE_REQUEST);
}