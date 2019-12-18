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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AES_INTR_MASK ; 
 int AES_INTR_PENDING ; 
 int AES_INTR_REG ; 
 int ENOMEM ; 
 int /*<<< orphan*/ * _iobase ; 
 int crypto_register_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  geode_alg ; 
 int /*<<< orphan*/  geode_cbc_alg ; 
 int /*<<< orphan*/  geode_ecb_alg ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/ * pci_iomap (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int geode_aes_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
	int ret;

	ret = pci_enable_device(dev);
	if (ret)
		return ret;

	ret = pci_request_regions(dev, "geode-aes");
	if (ret)
		goto eenable;

	_iobase = pci_iomap(dev, 0, 0);

	if (_iobase == NULL) {
		ret = -ENOMEM;
		goto erequest;
	}

	spin_lock_init(&lock);

	/* Clear any pending activity */
	iowrite32(AES_INTR_PENDING | AES_INTR_MASK, _iobase + AES_INTR_REG);

	ret = crypto_register_alg(&geode_alg);
	if (ret)
		goto eiomap;

	ret = crypto_register_alg(&geode_ecb_alg);
	if (ret)
		goto ealg;

	ret = crypto_register_alg(&geode_cbc_alg);
	if (ret)
		goto eecb;

	dev_notice(&dev->dev, "GEODE AES engine enabled.\n");
	return 0;

 eecb:
	crypto_unregister_alg(&geode_ecb_alg);

 ealg:
	crypto_unregister_alg(&geode_alg);

 eiomap:
	pci_iounmap(dev, _iobase);

 erequest:
	pci_release_regions(dev);

 eenable:
	pci_disable_device(dev);

	dev_err(&dev->dev, "GEODE AES initialization failed.\n");
	return ret;
}