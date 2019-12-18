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
struct nicpf {int flags; int /*<<< orphan*/  check_link_mtx; int /*<<< orphan*/  check_link; int /*<<< orphan*/  rss_ind_tbl_size; int /*<<< orphan*/  reg_base; int /*<<< orphan*/  node; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  NIC_MAX_RSS_IDR_TBL_SIZE ; 
 int NIC_TNS_ENABLED ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nicpf* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nic_get_node_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nic_init_hw (struct nicpf*) ; 
 int /*<<< orphan*/  nic_poll_for_link (struct nicpf*) ; 
 int nic_register_interrupts (struct nicpf*) ; 
 int /*<<< orphan*/  nic_set_lmac_vf_mapping (struct nicpf*) ; 
 int nic_sriov_init (int /*<<< orphan*/ ,struct nicpf*) ; 
 int /*<<< orphan*/  nic_unregister_interrupts (struct nicpf*) ; 
 int nicpf_alloc_res (struct nicpf*) ; 
 int /*<<< orphan*/  nicpf_free_res (struct nicpf*) ; 
 int /*<<< orphan*/  pci_disable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nicpf_attach(device_t dev)
{
	struct nicpf *nic;
	int err;

	nic = device_get_softc(dev);
	nic->dev = dev;

	/* Enable bus mastering */
	pci_enable_busmaster(dev);

	/* Allocate PCI resources */
	err = nicpf_alloc_res(nic);
	if (err != 0) {
		device_printf(dev, "Could not allocate PCI resources\n");
		return (err);
	}

	nic->node = nic_get_node_id(nic->reg_base);

	/* Enable Traffic Network Switch (TNS) bypass mode by default */
	nic->flags &= ~NIC_TNS_ENABLED;
	nic_set_lmac_vf_mapping(nic);

	/* Initialize hardware */
	nic_init_hw(nic);

	/* Set RSS TBL size for each VF */
	nic->rss_ind_tbl_size = NIC_MAX_RSS_IDR_TBL_SIZE;

	/* Setup interrupts */
	err = nic_register_interrupts(nic);
	if (err != 0)
		goto err_free_res;

	/* Configure SRIOV */
	err = nic_sriov_init(dev, nic);
	if (err != 0)
		goto err_free_intr;

	if (nic->flags & NIC_TNS_ENABLED)
		return (0);

	mtx_init(&nic->check_link_mtx, "VNIC PF link poll", NULL, MTX_DEF);
	/* Register physical link status poll callout */
	callout_init_mtx(&nic->check_link, &nic->check_link_mtx, 0);
	mtx_lock(&nic->check_link_mtx);
	nic_poll_for_link(nic);
	mtx_unlock(&nic->check_link_mtx);

	return (0);

err_free_intr:
	nic_unregister_interrupts(nic);
err_free_res:
	nicpf_free_res(nic);
	pci_disable_busmaster(dev);

	return (err);
}