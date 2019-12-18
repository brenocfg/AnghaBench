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
typedef  enum intr_trigger { ____Placeholder_intr_trigger } intr_trigger ;
typedef  enum intr_polarity { ____Placeholder_intr_polarity } intr_polarity ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int arm_config_irq (int,int,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int stub1 (int,int,int) ; 

__attribute__((used)) static int
nexus_config_intr(device_t dev, int irq, enum intr_trigger trig,
    enum intr_polarity pol)
{
	int ret = ENODEV;

#ifdef INTRNG
	device_printf(dev, "bus_config_intr is obsolete and not supported!\n");
	ret = EOPNOTSUPP;
#else
	if (arm_config_irq)
		ret = (*arm_config_irq)(irq, trig, pol);
#endif
	return (ret);
}