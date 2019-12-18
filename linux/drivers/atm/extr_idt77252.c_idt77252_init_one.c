#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {int dummy; } ;
struct pci_dev {int revision; int /*<<< orphan*/  dev; } ;
struct idt77252_dev {int revision; int index; int name; int sramsize; void* membase; struct idt77252_dev* next; int /*<<< orphan*/  link_pcr; int /*<<< orphan*/  vcibits; int /*<<< orphan*/  vpibits; void** fbq; struct atm_dev* atmdev; int /*<<< orphan*/  tst_timer; int /*<<< orphan*/  tst_lock; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  mutex; int /*<<< orphan*/  tqueue; struct pci_dev* pcidev; } ;
struct TYPE_3__ {int /*<<< orphan*/  vci_bits; int /*<<< orphan*/  vpi_bits; } ;
struct atm_dev {TYPE_2__* phy; int /*<<< orphan*/  link_rate; TYPE_1__ ci_range; struct idt77252_dev* dev_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* stop ) (struct atm_dev*) ;int /*<<< orphan*/  (* start ) (struct atm_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct atm_dev* atm_dev_register (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deinit_card (struct idt77252_dev*) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct idt77252_dev* idt77252_chain ; 
 scalar_t__ idt77252_dev_open (struct idt77252_dev*) ; 
 int /*<<< orphan*/  idt77252_ops ; 
 scalar_t__ idt77252_preset (struct idt77252_dev*) ; 
 int /*<<< orphan*/  idt77252_softint ; 
 scalar_t__ init_card (struct atm_dev*) ; 
 void* ioremap (unsigned long,int) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  kfree (struct idt77252_dev*) ; 
 struct idt77252_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int pci_name (struct pci_dev*) ; 
 unsigned long pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  printk (char*,int,...) ; 
 int probe_sram (struct idt77252_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct atm_dev*) ; 
 int /*<<< orphan*/  stub2 (struct atm_dev*) ; 
 int /*<<< orphan*/  suni_init (struct atm_dev*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tst_timer ; 

__attribute__((used)) static int idt77252_init_one(struct pci_dev *pcidev,
			     const struct pci_device_id *id)
{
	static struct idt77252_dev **last = &idt77252_chain;
	static int index = 0;

	unsigned long membase, srambase;
	struct idt77252_dev *card;
	struct atm_dev *dev;
	int i, err;


	if ((err = pci_enable_device(pcidev))) {
		printk("idt77252: can't enable PCI device at %s\n", pci_name(pcidev));
		return err;
	}

	if ((err = dma_set_mask_and_coherent(&pcidev->dev, DMA_BIT_MASK(32)))) {
		printk("idt77252: can't enable DMA for PCI device at %s\n", pci_name(pcidev));
		return err;
	}

	card = kzalloc(sizeof(struct idt77252_dev), GFP_KERNEL);
	if (!card) {
		printk("idt77252-%d: can't allocate private data\n", index);
		err = -ENOMEM;
		goto err_out_disable_pdev;
	}
	card->revision = pcidev->revision;
	card->index = index;
	card->pcidev = pcidev;
	sprintf(card->name, "idt77252-%d", card->index);

	INIT_WORK(&card->tqueue, idt77252_softint);

	membase = pci_resource_start(pcidev, 1);
	srambase = pci_resource_start(pcidev, 2);

	mutex_init(&card->mutex);
	spin_lock_init(&card->cmd_lock);
	spin_lock_init(&card->tst_lock);

	timer_setup(&card->tst_timer, tst_timer, 0);

	/* Do the I/O remapping... */
	card->membase = ioremap(membase, 1024);
	if (!card->membase) {
		printk("%s: can't ioremap() membase\n", card->name);
		err = -EIO;
		goto err_out_free_card;
	}

	if (idt77252_preset(card)) {
		printk("%s: preset failed\n", card->name);
		err = -EIO;
		goto err_out_iounmap;
	}

	dev = atm_dev_register("idt77252", &pcidev->dev, &idt77252_ops, -1,
			       NULL);
	if (!dev) {
		printk("%s: can't register atm device\n", card->name);
		err = -EIO;
		goto err_out_iounmap;
	}
	dev->dev_data = card;
	card->atmdev = dev;

#ifdef	CONFIG_ATM_IDT77252_USE_SUNI
	suni_init(dev);
	if (!dev->phy) {
		printk("%s: can't init SUNI\n", card->name);
		err = -EIO;
		goto err_out_deinit_card;
	}
#endif	/* CONFIG_ATM_IDT77252_USE_SUNI */

	card->sramsize = probe_sram(card);

	for (i = 0; i < 4; i++) {
		card->fbq[i] = ioremap(srambase | 0x200000 | (i << 18), 4);
		if (!card->fbq[i]) {
			printk("%s: can't ioremap() FBQ%d\n", card->name, i);
			err = -EIO;
			goto err_out_deinit_card;
		}
	}

	printk("%s: ABR SAR (Rev %c): MEM %08lx SRAM %08lx [%u KB]\n",
	       card->name, ((card->revision > 1) && (card->revision < 25)) ?
	       'A' + card->revision - 1 : '?', membase, srambase,
	       card->sramsize / 1024);

	if (init_card(dev)) {
		printk("%s: init_card failed\n", card->name);
		err = -EIO;
		goto err_out_deinit_card;
	}

	dev->ci_range.vpi_bits = card->vpibits;
	dev->ci_range.vci_bits = card->vcibits;
	dev->link_rate = card->link_pcr;

	if (dev->phy->start)
		dev->phy->start(dev);

	if (idt77252_dev_open(card)) {
		printk("%s: dev_open failed\n", card->name);
		err = -EIO;
		goto err_out_stop;
	}

	*last = card;
	last = &card->next;
	index++;

	return 0;

err_out_stop:
	if (dev->phy->stop)
		dev->phy->stop(dev);

err_out_deinit_card:
	deinit_card(card);

err_out_iounmap:
	iounmap(card->membase);

err_out_free_card:
	kfree(card);

err_out_disable_pdev:
	pci_disable_device(pcidev);
	return err;
}