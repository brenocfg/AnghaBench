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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int arm_remove_irqhandler (int /*<<< orphan*/ ,void*) ; 
 int intr_teardown_irq (int /*<<< orphan*/ ,struct resource*,void*) ; 
 int /*<<< orphan*/  rman_get_start (struct resource*) ; 

__attribute__((used)) static int
nexus_teardown_intr(device_t dev, device_t child, struct resource *r, void *ih)
{

#ifdef INTRNG
	return (intr_teardown_irq(child, r, ih));
#else
	return (arm_remove_irqhandler(rman_get_start(r), ih));
#endif
}