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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  driver_filter_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int INTR_EXCL ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  arm_setup_irqhandler (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int,int,void**) ; 
 int /*<<< orphan*/  arm_unmask_irq (int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int intr_setup_irq (int /*<<< orphan*/ ,struct resource*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int,void**) ; 
 int rman_get_end (struct resource*) ; 
 int rman_get_flags (struct resource*) ; 
 int rman_get_start (struct resource*) ; 

__attribute__((used)) static int
nexus_setup_intr(device_t dev, device_t child, struct resource *res, int flags,
    driver_filter_t *filt, driver_intr_t *intr, void *arg, void **cookiep)
{
#ifndef INTRNG
	int irq;
#endif

	if ((rman_get_flags(res) & RF_SHAREABLE) == 0)
		flags |= INTR_EXCL;

#ifdef INTRNG
	return(intr_setup_irq(child, res, filt, intr, arg, flags, cookiep));
#else
	for (irq = rman_get_start(res); irq <= rman_get_end(res); irq++) {
		arm_setup_irqhandler(device_get_nameunit(child),
		    filt, intr, arg, irq, flags, cookiep);
		arm_unmask_irq(irq);
	}
	return (0);
#endif
}