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
typedef  scalar_t__ iot_t ;

/* Variables and functions */
 scalar_t__ IOT_READ ; 
 scalar_t__ IOT_WRITE ; 
 int random () ; 

__attribute__((used)) static iot_t
choose_aio(iot_t iomask)
{
	/* choose a random read or write event, limited by the mask */
	if (iomask == IOT_READ)
		return IOT_READ;
	else if (iomask == IOT_WRITE)
		return IOT_WRITE;
	return (random() & 0x01 ? IOT_READ : IOT_WRITE);
}