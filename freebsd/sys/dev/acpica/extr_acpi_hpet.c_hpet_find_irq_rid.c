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
typedef  scalar_t__ u_long ;
typedef  scalar_t__ rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int bus_get_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
hpet_find_irq_rid(device_t dev, u_long start, u_long end)
{
	rman_res_t irq;
	int error, rid;

	for (rid = 0;; rid++) {
		error = bus_get_resource(dev, SYS_RES_IRQ, rid, &irq, NULL);
		if (error != 0 || (start <= irq && irq <= end))
			return (rid);
	}
}