#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* device_t ;
struct TYPE_5__ {scalar_t__ parent; } ;

/* Variables and functions */
 int BUS_GET_DOMAIN (scalar_t__,TYPE_1__*,int*) ; 
 int ENOENT ; 

int
bus_generic_get_domain(device_t dev, device_t child, int *domain)
{

	if (dev->parent)
		return (BUS_GET_DOMAIN(dev->parent, dev, domain));

	return (ENOENT);
}