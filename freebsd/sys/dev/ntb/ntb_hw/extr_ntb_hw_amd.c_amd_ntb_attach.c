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
struct amd_ntb_softc {int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  amd_init_side_info (struct amd_ntb_softc*) ; 
 int /*<<< orphan*/  amd_ntb_detach (int /*<<< orphan*/ ) ; 
 int amd_ntb_init (struct amd_ntb_softc*) ; 
 int amd_ntb_map_pci_bars (struct amd_ntb_softc*) ; 
 int /*<<< orphan*/  amd_ntb_spad_clear (struct amd_ntb_softc*) ; 
 int /*<<< orphan*/  amd_ntb_sysctl_init (struct amd_ntb_softc*) ; 
 struct amd_ntb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int ntb_register_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
amd_ntb_attach(device_t device)
{
	struct amd_ntb_softc *ntb = device_get_softc(device);
	int error;

	ntb->device = device;

	/* Enable PCI bus mastering for "device" */
	pci_enable_busmaster(ntb->device);

	error = amd_ntb_map_pci_bars(ntb);
	if (error)
		goto out;
		
	error = amd_ntb_init(ntb);
	if (error)
		goto out;

	amd_init_side_info(ntb);

	amd_ntb_spad_clear(ntb);

	amd_ntb_sysctl_init(ntb);

	/* Attach children to this controller */
	error = ntb_register_device(device);

out:
	if (error)
		amd_ntb_detach(device);

	return (error);
}