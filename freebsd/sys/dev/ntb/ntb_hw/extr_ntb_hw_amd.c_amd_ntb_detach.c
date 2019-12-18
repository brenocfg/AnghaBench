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
struct amd_ntb_softc {int /*<<< orphan*/  device; int /*<<< orphan*/  db_mask_lock; int /*<<< orphan*/  hb_timer; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  amd_deinit_side_info (struct amd_ntb_softc*) ; 
 int /*<<< orphan*/  amd_ntb_deinit_isr (struct amd_ntb_softc*) ; 
 int /*<<< orphan*/  amd_ntb_unmap_pci_bars (struct amd_ntb_softc*) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 struct amd_ntb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntb_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_busmaster (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
amd_ntb_detach(device_t device)
{
	struct amd_ntb_softc *ntb = device_get_softc(device);

	ntb_unregister_device(device);
	amd_deinit_side_info(ntb);
	callout_drain(&ntb->hb_timer);
	amd_ntb_deinit_isr(ntb);
	mtx_destroy(&ntb->db_mask_lock);
	pci_disable_busmaster(ntb->device);
	amd_ntb_unmap_pci_bars(ntb);

	return (0);
}