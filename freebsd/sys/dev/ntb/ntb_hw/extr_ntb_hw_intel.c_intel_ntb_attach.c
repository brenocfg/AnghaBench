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
struct ntb_softc {scalar_t__ type; int /*<<< orphan*/  device; int /*<<< orphan*/  db_mask_lock; int /*<<< orphan*/  peer_msix_work; int /*<<< orphan*/  lr_timer; int /*<<< orphan*/  heartbeat_timer; void* msix_mw_idx; void* b2b_mw_idx; int /*<<< orphan*/  features; } ;
struct ntb_hw_info {scalar_t__ type; int /*<<< orphan*/  features; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 void* B2B_MW_DISABLED ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 scalar_t__ NTB_ATOM ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 struct ntb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int intel_ntb_atom_init_dev (struct ntb_softc*) ; 
 int /*<<< orphan*/  intel_ntb_detach (int /*<<< orphan*/ ) ; 
 int intel_ntb_detect_atom (struct ntb_softc*) ; 
 int /*<<< orphan*/  intel_ntb_detect_max_mw (struct ntb_softc*) ; 
 int intel_ntb_detect_xeon (struct ntb_softc*) ; 
 struct ntb_hw_info* intel_ntb_get_device_info (int /*<<< orphan*/ ) ; 
 int intel_ntb_map_pci_bars (struct ntb_softc*) ; 
 int /*<<< orphan*/  intel_ntb_poll_link (struct ntb_softc*) ; 
 int /*<<< orphan*/  intel_ntb_spad_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ntb_sysctl_init (struct ntb_softc*) ; 
 int intel_ntb_xeon_init_dev (struct ntb_softc*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ntb_register_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_devid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
intel_ntb_attach(device_t device)
{
	struct ntb_softc *ntb;
	struct ntb_hw_info *p;
	int error;

	ntb = device_get_softc(device);
	p = intel_ntb_get_device_info(pci_get_devid(device));

	ntb->device = device;
	ntb->type = p->type;
	ntb->features = p->features;
	ntb->b2b_mw_idx = B2B_MW_DISABLED;
	ntb->msix_mw_idx = B2B_MW_DISABLED;

	/* Heartbeat timer for NTB_ATOM since there is no link interrupt */
	callout_init(&ntb->heartbeat_timer, 1);
	callout_init(&ntb->lr_timer, 1);
	callout_init(&ntb->peer_msix_work, 1);
	mtx_init(&ntb->db_mask_lock, "ntb hw bits", NULL, MTX_SPIN);

	if (ntb->type == NTB_ATOM)
		error = intel_ntb_detect_atom(ntb);
	else
		error = intel_ntb_detect_xeon(ntb);
	if (error != 0)
		goto out;

	intel_ntb_detect_max_mw(ntb);

	pci_enable_busmaster(ntb->device);

	error = intel_ntb_map_pci_bars(ntb);
	if (error != 0)
		goto out;
	if (ntb->type == NTB_ATOM)
		error = intel_ntb_atom_init_dev(ntb);
	else
		error = intel_ntb_xeon_init_dev(ntb);
	if (error != 0)
		goto out;

	intel_ntb_spad_clear(device);

	intel_ntb_poll_link(ntb);

	intel_ntb_sysctl_init(ntb);

	/* Attach children to this controller */
	error = ntb_register_device(device);

out:
	if (error != 0)
		intel_ntb_detach(device);
	return (error);
}