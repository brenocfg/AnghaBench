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
struct isci_softc {int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct isci_softc* DEVICE2SOFTC (int /*<<< orphan*/ ) ; 
 struct isci_softc* g_isci ; 
 int /*<<< orphan*/  isci_allocate_pci_memory (struct isci_softc*) ; 
 int /*<<< orphan*/  isci_detach (int /*<<< orphan*/ ) ; 
 int isci_initialize (struct isci_softc*) ; 
 int /*<<< orphan*/  isci_interrupt_setup (struct isci_softc*) ; 
 int /*<<< orphan*/  isci_sysctl_initialize (struct isci_softc*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
isci_attach(device_t device)
{
	int error;
	struct isci_softc *isci = DEVICE2SOFTC(device);

	g_isci = isci;
	isci->device = device;
	pci_enable_busmaster(device);

	isci_allocate_pci_memory(isci);

	error = isci_initialize(isci);

	if (error)
	{
		isci_detach(device);
		return (error);
	}

	isci_interrupt_setup(isci);
	isci_sysctl_initialize(isci);

	return (0);
}