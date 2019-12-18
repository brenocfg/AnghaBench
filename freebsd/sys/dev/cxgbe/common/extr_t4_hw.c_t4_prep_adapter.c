#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int cclk; } ;
struct TYPE_6__ {int /*<<< orphan*/  vpd_cap_addr; } ;
struct TYPE_4__ {int rev; int cim_la_size; int fpga; int nports; int portvec; TYPE_2__ vpd; int /*<<< orphan*/  b_wnd; int /*<<< orphan*/  a_wnd; TYPE_3__ pci; int /*<<< orphan*/  chipid; } ;
struct adapter {TYPE_1__ params; int /*<<< orphan*/ * chip_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_PL_REV ; 
 int /*<<< orphan*/  CHELSIO_T4 ; 
 int /*<<< orphan*/  CH_ALERT (struct adapter*,char*) ; 
 int CIMLA_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  G_CHIPID (int /*<<< orphan*/ ) ; 
 int G_REV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_CAP_ID_VPD ; 
 int /*<<< orphan*/  PCI_DEVICE_ID ; 
 int chip_id (struct adapter*) ; 
 int /*<<< orphan*/  get_pci_mode (struct adapter*,TYPE_3__*) ; 
 int get_vpd_params (struct adapter*,TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_cong_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pcie_completion_timeout (struct adapter*,int) ; 
 int /*<<< orphan*/ * t4_get_chip_params (int) ; 
 int t4_get_flash_params (struct adapter*) ; 
 int /*<<< orphan*/  t4_os_find_pci_capability (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_os_pci_read_cfg2 (struct adapter*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

int t4_prep_adapter(struct adapter *adapter, u32 *buf)
{
	int ret;
	uint16_t device_id;
	uint32_t pl_rev;

	get_pci_mode(adapter, &adapter->params.pci);

	pl_rev = t4_read_reg(adapter, A_PL_REV);
	adapter->params.chipid = G_CHIPID(pl_rev);
	adapter->params.rev = G_REV(pl_rev);
	if (adapter->params.chipid == 0) {
		/* T4 did not have chipid in PL_REV (T5 onwards do) */
		adapter->params.chipid = CHELSIO_T4;

		/* T4A1 chip is not supported */
		if (adapter->params.rev == 1) {
			CH_ALERT(adapter, "T4 rev 1 chip is not supported.\n");
			return -EINVAL;
		}
	}

	adapter->chip_params = t4_get_chip_params(chip_id(adapter));
	if (adapter->chip_params == NULL)
		return -EINVAL;

	adapter->params.pci.vpd_cap_addr =
	    t4_os_find_pci_capability(adapter, PCI_CAP_ID_VPD);

	ret = t4_get_flash_params(adapter);
	if (ret < 0)
		return ret;

	/* Cards with real ASICs have the chipid in the PCIe device id */
	t4_os_pci_read_cfg2(adapter, PCI_DEVICE_ID, &device_id);
	if (device_id >> 12 == chip_id(adapter))
		adapter->params.cim_la_size = CIMLA_SIZE;
	else {
		/* FPGA */
		adapter->params.fpga = 1;
		adapter->params.cim_la_size = 2 * CIMLA_SIZE;
	}

	ret = get_vpd_params(adapter, &adapter->params.vpd, device_id, buf);
	if (ret < 0)
		return ret;

	init_cong_ctrl(adapter->params.a_wnd, adapter->params.b_wnd);

	/*
	 * Default port and clock for debugging in case we can't reach FW.
	 */
	adapter->params.nports = 1;
	adapter->params.portvec = 1;
	adapter->params.vpd.cclk = 50000;

	/* Set pci completion timeout value to 4 seconds. */
	set_pcie_completion_timeout(adapter, 0xd);
	return 0;
}