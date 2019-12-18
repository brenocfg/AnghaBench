#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ntb_softc {int /*<<< orphan*/  device; TYPE_1__* bar_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  pbarxlat_off; int /*<<< orphan*/  ssz_off; int /*<<< orphan*/  psz_off; void* pci_resource_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_FEATURE (struct ntb_softc*,int /*<<< orphan*/ ) ; 
 size_t NTB_B2B_BAR_1 ; 
 size_t NTB_B2B_BAR_2 ; 
 size_t NTB_B2B_BAR_3 ; 
 size_t NTB_CONFIG_BAR ; 
 int /*<<< orphan*/  NTB_SPLIT_BAR ; 
 void* PCIR_BAR (int) ; 
 int /*<<< orphan*/  XEON_PBAR23SZ_OFFSET ; 
 int /*<<< orphan*/  XEON_PBAR2XLAT_OFFSET ; 
 int /*<<< orphan*/  XEON_PBAR4SZ_OFFSET ; 
 int /*<<< orphan*/  XEON_PBAR4XLAT_OFFSET ; 
 int /*<<< orphan*/  XEON_PBAR5SZ_OFFSET ; 
 int /*<<< orphan*/  XEON_PBAR5XLAT_OFFSET ; 
 int /*<<< orphan*/  XEON_SBAR23SZ_OFFSET ; 
 int /*<<< orphan*/  XEON_SBAR4SZ_OFFSET ; 
 int /*<<< orphan*/  XEON_SBAR5SZ_OFFSET ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int map_memory_window_bar (struct ntb_softc*,TYPE_1__*) ; 
 int map_mmr_bar (struct ntb_softc*,TYPE_1__*) ; 

__attribute__((used)) static int
intel_ntb_map_pci_bars(struct ntb_softc *ntb)
{
	int rc;

	ntb->bar_info[NTB_CONFIG_BAR].pci_resource_id = PCIR_BAR(0);
	rc = map_mmr_bar(ntb, &ntb->bar_info[NTB_CONFIG_BAR]);
	if (rc != 0)
		goto out;

	ntb->bar_info[NTB_B2B_BAR_1].pci_resource_id = PCIR_BAR(2);
	rc = map_memory_window_bar(ntb, &ntb->bar_info[NTB_B2B_BAR_1]);
	if (rc != 0)
		goto out;
	ntb->bar_info[NTB_B2B_BAR_1].psz_off = XEON_PBAR23SZ_OFFSET;
	ntb->bar_info[NTB_B2B_BAR_1].ssz_off = XEON_SBAR23SZ_OFFSET;
	ntb->bar_info[NTB_B2B_BAR_1].pbarxlat_off = XEON_PBAR2XLAT_OFFSET;

	ntb->bar_info[NTB_B2B_BAR_2].pci_resource_id = PCIR_BAR(4);
	rc = map_memory_window_bar(ntb, &ntb->bar_info[NTB_B2B_BAR_2]);
	if (rc != 0)
		goto out;
	ntb->bar_info[NTB_B2B_BAR_2].psz_off = XEON_PBAR4SZ_OFFSET;
	ntb->bar_info[NTB_B2B_BAR_2].ssz_off = XEON_SBAR4SZ_OFFSET;
	ntb->bar_info[NTB_B2B_BAR_2].pbarxlat_off = XEON_PBAR4XLAT_OFFSET;

	if (!HAS_FEATURE(ntb, NTB_SPLIT_BAR))
		goto out;

	ntb->bar_info[NTB_B2B_BAR_3].pci_resource_id = PCIR_BAR(5);
	rc = map_memory_window_bar(ntb, &ntb->bar_info[NTB_B2B_BAR_3]);
	ntb->bar_info[NTB_B2B_BAR_3].psz_off = XEON_PBAR5SZ_OFFSET;
	ntb->bar_info[NTB_B2B_BAR_3].ssz_off = XEON_SBAR5SZ_OFFSET;
	ntb->bar_info[NTB_B2B_BAR_3].pbarxlat_off = XEON_PBAR5XLAT_OFFSET;

out:
	if (rc != 0)
		device_printf(ntb->device,
		    "unable to allocate pci resource\n");
	return (rc);
}