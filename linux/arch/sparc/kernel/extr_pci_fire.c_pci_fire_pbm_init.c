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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct pci_pbm_info {int config_space_reg_bits; struct pci_pbm_info* next; int /*<<< orphan*/  pci_bus; int /*<<< orphan*/  name; scalar_t__ controller_regs; scalar_t__ pbm_regs; struct platform_device* op; int /*<<< orphan*/  portid; scalar_t__ index; int /*<<< orphan*/ * pci_ops; int /*<<< orphan*/  numa_node; } ;
struct linux_prom64_registers {scalar_t__ phys_addr; } ;
struct device_node {int /*<<< orphan*/  full_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 struct linux_prom64_registers* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_determine_mem_io_space (struct pci_pbm_info*) ; 
 int /*<<< orphan*/  pci_fire_hw_init (struct pci_pbm_info*) ; 
 int /*<<< orphan*/  pci_fire_msi_init (struct pci_pbm_info*) ; 
 int pci_fire_pbm_iommu_init (struct pci_pbm_info*) ; 
 int /*<<< orphan*/  pci_get_pbm_props (struct pci_pbm_info*) ; 
 int /*<<< orphan*/  pci_num_pbms ; 
 struct pci_pbm_info* pci_pbm_root ; 
 int /*<<< orphan*/  pci_scan_one_pbm (struct pci_pbm_info*,TYPE_1__*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun4u_pci_ops ; 

__attribute__((used)) static int pci_fire_pbm_init(struct pci_pbm_info *pbm,
			     struct platform_device *op, u32 portid)
{
	const struct linux_prom64_registers *regs;
	struct device_node *dp = op->dev.of_node;
	int err;

	pbm->numa_node = NUMA_NO_NODE;

	pbm->pci_ops = &sun4u_pci_ops;
	pbm->config_space_reg_bits = 12;

	pbm->index = pci_num_pbms++;

	pbm->portid = portid;
	pbm->op = op;
	pbm->name = dp->full_name;

	regs = of_get_property(dp, "reg", NULL);
	pbm->pbm_regs = regs[0].phys_addr;
	pbm->controller_regs = regs[1].phys_addr - 0x410000UL;

	printk("%s: SUN4U PCIE Bus Module\n", pbm->name);

	pci_determine_mem_io_space(pbm);

	pci_get_pbm_props(pbm);

	pci_fire_hw_init(pbm);

	err = pci_fire_pbm_iommu_init(pbm);
	if (err)
		return err;

	pci_fire_msi_init(pbm);

	pbm->pci_bus = pci_scan_one_pbm(pbm, &op->dev);

	/* XXX register error interrupt handlers XXX */

	pbm->next = pci_pbm_root;
	pci_pbm_root = pbm;

	return 0;
}