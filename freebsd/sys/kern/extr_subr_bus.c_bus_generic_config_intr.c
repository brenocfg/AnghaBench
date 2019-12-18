#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum intr_trigger { ____Placeholder_intr_trigger } intr_trigger ;
typedef  enum intr_polarity { ____Placeholder_intr_polarity } intr_polarity ;
typedef  TYPE_1__* device_t ;
struct TYPE_3__ {scalar_t__ parent; } ;

/* Variables and functions */
 int BUS_CONFIG_INTR (scalar_t__,int,int,int) ; 
 int EINVAL ; 

int
bus_generic_config_intr(device_t dev, int irq, enum intr_trigger trig,
    enum intr_polarity pol)
{

	/* Propagate up the bus hierarchy until someone handles it. */
	if (dev->parent)
		return (BUS_CONFIG_INTR(dev->parent, irq, trig, pol));
	return (EINVAL);
}