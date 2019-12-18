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
 int /*<<< orphan*/  al_pcib_fixup (int /*<<< orphan*/ ) ; 
 int pci_host_generic_attach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
al_pcib_attach(device_t dev)
{
	int rv;

	rv = pci_host_generic_attach(dev);

	/* Annapurna quirk: configure vendor-specific registers */
	if (rv == 0)
		al_pcib_fixup(dev);

	return (rv);
}