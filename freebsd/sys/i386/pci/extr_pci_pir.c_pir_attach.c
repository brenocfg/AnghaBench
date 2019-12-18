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
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_pir_parse () ; 
 int /*<<< orphan*/ * pir_device ; 

__attribute__((used)) static int
pir_attach(device_t dev)
{

	pci_pir_parse();
	KASSERT(pir_device == NULL, ("Multiple pir devices"));
	pir_device = dev;
	return (0);
}