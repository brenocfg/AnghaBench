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
 int PCI_SLOTMAX ; 

__attribute__((used)) static int
thunder_pem_maxslots(device_t dev)
{

#if 0
	/* max slots per bus acc. to standard */
	return (PCI_SLOTMAX);
#else
	/*
	 * ARM64TODO Workaround - otherwise an em(4) interface appears to be
	 * present on every PCI function on the bus to which it is connected
	 */
	return (0);
#endif
}