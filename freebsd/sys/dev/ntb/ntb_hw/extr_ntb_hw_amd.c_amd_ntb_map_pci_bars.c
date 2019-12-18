#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct amd_ntb_softc {TYPE_1__* bar_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  limit_off; int /*<<< orphan*/  xlat_off; void* pci_resource_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_BAR1LMT_OFFSET ; 
 int /*<<< orphan*/  AMD_BAR1XLAT_OFFSET ; 
 int /*<<< orphan*/  AMD_BAR23LMT_OFFSET ; 
 int /*<<< orphan*/  AMD_BAR23XLAT_OFFSET ; 
 int /*<<< orphan*/  AMD_BAR45LMT_OFFSET ; 
 int /*<<< orphan*/  AMD_BAR45XLAT_OFFSET ; 
 size_t NTB_BAR_1 ; 
 size_t NTB_BAR_2 ; 
 size_t NTB_BAR_3 ; 
 size_t NTB_CONFIG_BAR ; 
 void* PCIR_BAR (int) ; 
 int /*<<< orphan*/  amd_ntb_printf (int /*<<< orphan*/ ,char*) ; 
 int map_bar (struct amd_ntb_softc*,TYPE_1__*) ; 

__attribute__((used)) static int
amd_ntb_map_pci_bars(struct amd_ntb_softc *ntb)
{
	int rc = 0;

	/* NTB Config/Control registers - BAR 0 */
	ntb->bar_info[NTB_CONFIG_BAR].pci_resource_id = PCIR_BAR(0);
	rc = map_bar(ntb, &ntb->bar_info[NTB_CONFIG_BAR]);
	if (rc != 0)
		goto out;

	/* Memory Window 0 BAR - BAR 1 */
	ntb->bar_info[NTB_BAR_1].pci_resource_id = PCIR_BAR(1);
	rc = map_bar(ntb, &ntb->bar_info[NTB_BAR_1]);
	if (rc != 0)
		goto out;
	ntb->bar_info[NTB_BAR_1].xlat_off = AMD_BAR1XLAT_OFFSET;
	ntb->bar_info[NTB_BAR_1].limit_off = AMD_BAR1LMT_OFFSET;

	/* Memory Window 1 BAR - BAR 2&3 */
	ntb->bar_info[NTB_BAR_2].pci_resource_id = PCIR_BAR(2);
	rc = map_bar(ntb, &ntb->bar_info[NTB_BAR_2]);
	if (rc != 0)
		goto out;
	ntb->bar_info[NTB_BAR_2].xlat_off = AMD_BAR23XLAT_OFFSET;
	ntb->bar_info[NTB_BAR_2].limit_off = AMD_BAR23LMT_OFFSET;

	/* Memory Window 2 BAR - BAR 4&5 */
	ntb->bar_info[NTB_BAR_3].pci_resource_id = PCIR_BAR(4);
	rc = map_bar(ntb, &ntb->bar_info[NTB_BAR_3]);
	if (rc != 0)
		goto out;
	ntb->bar_info[NTB_BAR_3].xlat_off = AMD_BAR45XLAT_OFFSET;
	ntb->bar_info[NTB_BAR_3].limit_off = AMD_BAR45LMT_OFFSET;

out:
	if (rc != 0)
		amd_ntb_printf(0, "unable to allocate pci resource\n");

	return (rc);
}