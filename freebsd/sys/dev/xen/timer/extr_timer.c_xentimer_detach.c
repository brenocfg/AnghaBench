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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EBUSY ; 

__attribute__((used)) static int
xentimer_detach(device_t dev)
{

	/* Implement Xen PV clock teardown - XXX see hpet_detach ? */
	/* If possible:
	 * 1. need to deregister timecounter
	 * 2. need to deregister event timer
	 * 3. need to deregister virtual IRQ event channels
	 */
	return (EBUSY);
}