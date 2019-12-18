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
typedef  int /*<<< orphan*/  register_t ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  driver_filter_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int NUM_MIPS_IRQS ; 
 int /*<<< orphan*/  cpu_establish_hardintr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int,int,void**) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 
 int intr_setup_irq (int /*<<< orphan*/ ,struct resource*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int,void**) ; 
 int rman_get_start (struct resource*) ; 

__attribute__((used)) static int
nexus_setup_intr(device_t dev, device_t child, struct resource *res, int flags,
    driver_filter_t *filt, driver_intr_t *intr, void *arg, void **cookiep)
{
#ifdef INTRNG
	return (intr_setup_irq(child, res, filt, intr, arg, flags, cookiep));
#else
	int irq;
	register_t s;

	s = intr_disable();
	irq = rman_get_start(res);
	if (irq >= NUM_MIPS_IRQS) {
		intr_restore(s);
		return (0);
	}

	cpu_establish_hardintr(device_get_nameunit(child), filt, intr, arg,
	    irq, flags, cookiep);
	intr_restore(s);

	return (0);
#endif
}