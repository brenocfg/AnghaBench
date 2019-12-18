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
 int sioattach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int sioprobe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int) ; 

__attribute__((used)) static int
sio_pccard_attach(device_t dev)
{
	int err;

	/* Do not probe IRQ - pccard doesn't turn on the interrupt line */
	/* until bus_setup_intr */
	if ((err = sioprobe(dev, 0, 0UL, 1)) > 0)
		return (err);
	return (sioattach(dev, 0, 0UL));
}