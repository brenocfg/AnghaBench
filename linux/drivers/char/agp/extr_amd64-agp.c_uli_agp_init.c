#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  bus; } ;
struct TYPE_5__ {struct pci_dev* misc; } ;
struct TYPE_4__ {unsigned int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD64_GARTAPERTUREBASE ; 
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENODEV ; 
 int PCI_BASE_ADDRESS_MEM_MASK ; 
 int /*<<< orphan*/  PCI_DEVFN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ULI_X86_64_BASE_ADDR ; 
 int /*<<< orphan*/  ULI_X86_64_ENU_SCR_REG ; 
 int /*<<< orphan*/  ULI_X86_64_HTT_FEA_REG ; 
 unsigned int amd64_fetch_size () ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_2__* node_to_amd_nb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* uli_sizes ; 

__attribute__((used)) static int uli_agp_init(struct pci_dev *pdev)
{
	u32 httfea,baseaddr,enuscr;
	struct pci_dev *dev1;
	int i, ret;
	unsigned size = amd64_fetch_size();

	dev_info(&pdev->dev, "setting up ULi AGP\n");
	dev1 = pci_get_slot (pdev->bus,PCI_DEVFN(0,0));
	if (dev1 == NULL) {
		dev_info(&pdev->dev, "can't find ULi secondary device\n");
		return -ENODEV;
	}

	for (i = 0; i < ARRAY_SIZE(uli_sizes); i++)
		if (uli_sizes[i].size == size)
			break;

	if (i == ARRAY_SIZE(uli_sizes)) {
		dev_info(&pdev->dev, "no ULi size found for %d\n", size);
		ret = -ENODEV;
		goto put;
	}

	/* shadow x86-64 registers into ULi registers */
	pci_read_config_dword (node_to_amd_nb(0)->misc, AMD64_GARTAPERTUREBASE,
			       &httfea);

	/* if x86-64 aperture base is beyond 4G, exit here */
	if ((httfea & 0x7fff) >> (32 - 25)) {
		ret = -ENODEV;
		goto put;
	}

	httfea = (httfea& 0x7fff) << 25;

	pci_read_config_dword(pdev, ULI_X86_64_BASE_ADDR, &baseaddr);
	baseaddr&= ~PCI_BASE_ADDRESS_MEM_MASK;
	baseaddr|= httfea;
	pci_write_config_dword(pdev, ULI_X86_64_BASE_ADDR, baseaddr);

	enuscr= httfea+ (size * 1024 * 1024) - 1;
	pci_write_config_dword(dev1, ULI_X86_64_HTT_FEA_REG, httfea);
	pci_write_config_dword(dev1, ULI_X86_64_ENU_SCR_REG, enuscr);
	ret = 0;
put:
	pci_dev_put(dev1);
	return ret;
}