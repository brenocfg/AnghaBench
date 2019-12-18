#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource_list {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {struct resource_list resources; } ;
typedef  TYPE_1__ atkbdc_device_t ;

/* Variables and functions */
 scalar_t__ device_get_ivars (int /*<<< orphan*/ ) ; 

struct resource_list
*atkbdc_get_resource_list(device_t bus, device_t dev)
{
	atkbdc_device_t *ivar;

	ivar = (atkbdc_device_t *)device_get_ivars(dev);
	return &ivar->resources;
}