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
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 int isab_attach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
isab_pci_attach(device_t dev)
{

	bus_generic_probe(dev);
	return (isab_attach(dev));
}