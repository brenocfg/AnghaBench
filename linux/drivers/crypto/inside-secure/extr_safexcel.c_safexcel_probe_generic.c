#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct safexcel_ring_irq_data {int ring; struct safexcel_crypto_priv* priv; } ;
struct TYPE_5__ {int rings; } ;
struct TYPE_8__ {int hwdataw; int hwcfsize; int hwrfsize; void* algo_flags; void* pever; void* hiaver; void* hwver; } ;
struct safexcel_crypto_priv {int flags; scalar_t__ version; int /*<<< orphan*/  ring_used; TYPE_3__* ring; TYPE_1__ config; TYPE_4__ hwconfig; struct device* dev; scalar_t__ base; int /*<<< orphan*/  context_pool; } ;
struct safexcel_context_record {int dummy; } ;
struct pci_dev {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int ring; int /*<<< orphan*/  work; struct safexcel_crypto_priv* priv; } ;
struct TYPE_7__ {int busy; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; scalar_t__ requests; int /*<<< orphan*/  workqueue; TYPE_2__ work_data; void* rdr_req; int /*<<< orphan*/  rdr; int /*<<< orphan*/  cdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PCI ; 
 int EIP197_CFSIZE_ADJUST ; 
 int EIP197_CFSIZE_MASK ; 
 int EIP197_CFSIZE_OFFSET ; 
 int EIP197_DEFAULT_RING_SIZE ; 
 scalar_t__ EIP197_DEVBRD ; 
 scalar_t__ EIP197_GLOBAL (struct safexcel_crypto_priv*) ; 
 scalar_t__ EIP197_HIA_AIC (struct safexcel_crypto_priv*) ; 
 scalar_t__ EIP197_HIA_AIC_BASE ; 
 scalar_t__ EIP197_HIA_MST_CTRL ; 
 scalar_t__ EIP197_HIA_OPTIONS ; 
 scalar_t__ EIP197_HIA_VERSION ; 
 scalar_t__ EIP197_HIA_VERSION_BE ; 
 scalar_t__ EIP197_HIA_VERSION_LE ; 
 int EIP197_HWDATAW_MASK ; 
 int EIP197_HWDATAW_OFFSET ; 
 int /*<<< orphan*/  EIP197_IRQ_NUMBER (int,int) ; 
 int EIP197_MST_CTRL_BYTE_SWAP_BITS ; 
 scalar_t__ EIP197_PE (struct safexcel_crypto_priv*) ; 
 scalar_t__ EIP197_PE_EIP96_OPTIONS (int /*<<< orphan*/ ) ; 
 scalar_t__ EIP197_PE_EIP96_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ EIP197_REG_HI16 (int) ; 
 scalar_t__ EIP197_REG_LO16 (int) ; 
 int EIP197_RFSIZE_ADJUST ; 
 int EIP197_RFSIZE_MASK ; 
 int EIP197_RFSIZE_OFFSET ; 
 scalar_t__ EIP197_VERSION ; 
 scalar_t__ EIP197_VERSION_LE ; 
 void* EIP197_VERSION_MASK (int) ; 
 void* EIP197_VERSION_SWAP (int) ; 
 scalar_t__ EIP96_VERSION_LE ; 
 int EIP97_CFSIZE_MASK ; 
 int EIP97_CFSIZE_OFFSET ; 
 scalar_t__ EIP97_HIA_AIC_BASE ; 
 int EIP97_HWDATAW_MASK ; 
 int EIP97_RFSIZE_MASK ; 
 int EIP97_RFSIZE_OFFSET ; 
 scalar_t__ EIP97_VERSION_LE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int PCI_IRQ_MSI ; 
 int PCI_IRQ_MSIX ; 
 int SAFEXCEL_HW_EIP197 ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  crypto_init_queue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int,void*,int,void*,int,int,int,void*,void*) ; 
 void* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct safexcel_ring_irq_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmam_pool_create (char*,struct device*,int,int,int /*<<< orphan*/ ) ; 
 int pci_alloc_irq_vectors (struct pci_dev*,int,int,int) ; 
 void* readl (scalar_t__) ; 
 int /*<<< orphan*/  safexcel_configure (struct safexcel_crypto_priv*) ; 
 int /*<<< orphan*/  safexcel_dequeue_work ; 
 int safexcel_hw_init (struct safexcel_crypto_priv*) ; 
 int /*<<< orphan*/  safexcel_init_register_offsets (struct safexcel_crypto_priv*) ; 
 int safexcel_init_ring_descriptors (struct safexcel_crypto_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  safexcel_irq_ring ; 
 int /*<<< orphan*/  safexcel_irq_ring_thread ; 
 int safexcel_register_algorithms (struct safexcel_crypto_priv*) ; 
 int safexcel_request_ring_irq (void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct safexcel_ring_irq_data*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int safexcel_probe_generic(void *pdev,
				  struct safexcel_crypto_priv *priv,
				  int is_pci_dev)
{
	struct device *dev = priv->dev;
	u32 peid, version, mask, val, hiaopt;
	int i, ret, hwctg;

	priv->context_pool = dmam_pool_create("safexcel-context", dev,
					      sizeof(struct safexcel_context_record),
					      1, 0);
	if (!priv->context_pool)
		return -ENOMEM;

	/*
	 * First try the EIP97 HIA version regs
	 * For the EIP197, this is guaranteed to NOT return any of the test
	 * values
	 */
	version = readl(priv->base + EIP97_HIA_AIC_BASE + EIP197_HIA_VERSION);

	mask = 0;  /* do not swap */
	if (EIP197_REG_LO16(version) == EIP197_HIA_VERSION_LE) {
		priv->hwconfig.hiaver = EIP197_VERSION_MASK(version);
	} else if (EIP197_REG_HI16(version) == EIP197_HIA_VERSION_BE) {
		/* read back byte-swapped, so complement byte swap bits */
		mask = EIP197_MST_CTRL_BYTE_SWAP_BITS;
		priv->hwconfig.hiaver = EIP197_VERSION_SWAP(version);
	} else {
		/* So it wasn't an EIP97 ... maybe it's an EIP197? */
		version = readl(priv->base + EIP197_HIA_AIC_BASE +
				EIP197_HIA_VERSION);
		if (EIP197_REG_LO16(version) == EIP197_HIA_VERSION_LE) {
			priv->hwconfig.hiaver = EIP197_VERSION_MASK(version);
			priv->flags |= SAFEXCEL_HW_EIP197;
		} else if (EIP197_REG_HI16(version) ==
			   EIP197_HIA_VERSION_BE) {
			/* read back byte-swapped, so complement swap bits */
			mask = EIP197_MST_CTRL_BYTE_SWAP_BITS;
			priv->hwconfig.hiaver = EIP197_VERSION_SWAP(version);
			priv->flags |= SAFEXCEL_HW_EIP197;
		} else {
			return -ENODEV;
		}
	}

	/* Now initialize the reg offsets based on the probing info so far */
	safexcel_init_register_offsets(priv);

	/*
	 * If the version was read byte-swapped, we need to flip the device
	 * swapping Keep in mind here, though, that what we write will also be
	 * byte-swapped ...
	 */
	if (mask) {
		val = readl(EIP197_HIA_AIC(priv) + EIP197_HIA_MST_CTRL);
		val = val ^ (mask >> 24); /* toggle byte swap bits */
		writel(val, EIP197_HIA_AIC(priv) + EIP197_HIA_MST_CTRL);
	}

	/*
	 * We're not done probing yet! We may fall through to here if no HIA
	 * was found at all. So, with the endianness presumably correct now and
	 * the offsets setup, *really* probe for the EIP97/EIP197.
	 */
	version = readl(EIP197_GLOBAL(priv) + EIP197_VERSION);
	if (((priv->flags & SAFEXCEL_HW_EIP197) &&
	     (EIP197_REG_LO16(version) != EIP197_VERSION_LE)) ||
	    ((!(priv->flags & SAFEXCEL_HW_EIP197) &&
	     (EIP197_REG_LO16(version) != EIP97_VERSION_LE)))) {
		/*
		 * We did not find the device that matched our initial probing
		 * (or our initial probing failed) Report appropriate error.
		 */
		return -ENODEV;
	}

	priv->hwconfig.hwver = EIP197_VERSION_MASK(version);
	hwctg = version >> 28;
	peid = version & 255;

	/* Detect EIP96 packet engine and version */
	version = readl(EIP197_PE(priv) + EIP197_PE_EIP96_VERSION(0));
	if (EIP197_REG_LO16(version) != EIP96_VERSION_LE) {
		dev_err(dev, "EIP%d: EIP96 not detected.\n", peid);
		return -ENODEV;
	}
	priv->hwconfig.pever = EIP197_VERSION_MASK(version);

	hiaopt = readl(EIP197_HIA_AIC(priv) + EIP197_HIA_OPTIONS);

	if (priv->flags & SAFEXCEL_HW_EIP197) {
		/* EIP197 */
		priv->hwconfig.hwdataw  = (hiaopt >> EIP197_HWDATAW_OFFSET) &
					  EIP197_HWDATAW_MASK;
		priv->hwconfig.hwcfsize = ((hiaopt >> EIP197_CFSIZE_OFFSET) &
					   EIP197_CFSIZE_MASK) +
					  EIP197_CFSIZE_ADJUST;
		priv->hwconfig.hwrfsize = ((hiaopt >> EIP197_RFSIZE_OFFSET) &
					   EIP197_RFSIZE_MASK) +
					  EIP197_RFSIZE_ADJUST;
	} else {
		/* EIP97 */
		priv->hwconfig.hwdataw  = (hiaopt >> EIP197_HWDATAW_OFFSET) &
					  EIP97_HWDATAW_MASK;
		priv->hwconfig.hwcfsize = (hiaopt >> EIP97_CFSIZE_OFFSET) &
					  EIP97_CFSIZE_MASK;
		priv->hwconfig.hwrfsize = (hiaopt >> EIP97_RFSIZE_OFFSET) &
					  EIP97_RFSIZE_MASK;
	}

	/* Get supported algorithms from EIP96 transform engine */
	priv->hwconfig.algo_flags = readl(EIP197_PE(priv) +
				    EIP197_PE_EIP96_OPTIONS(0));

	/* Print single info line describing what we just detected */
	dev_info(priv->dev, "EIP%d:%x(%d)-HIA:%x(%d,%d,%d),PE:%x,alg:%08x\n",
		 peid, priv->hwconfig.hwver, hwctg, priv->hwconfig.hiaver,
		 priv->hwconfig.hwdataw, priv->hwconfig.hwcfsize,
		 priv->hwconfig.hwrfsize, priv->hwconfig.pever,
		 priv->hwconfig.algo_flags);

	safexcel_configure(priv);

	if (IS_ENABLED(CONFIG_PCI) && priv->version == EIP197_DEVBRD) {
		/*
		 * Request MSI vectors for global + 1 per ring -
		 * or just 1 for older dev images
		 */
		struct pci_dev *pci_pdev = pdev;

		ret = pci_alloc_irq_vectors(pci_pdev,
					    priv->config.rings + 1,
					    priv->config.rings + 1,
					    PCI_IRQ_MSI | PCI_IRQ_MSIX);
		if (ret < 0) {
			dev_err(dev, "Failed to allocate PCI MSI interrupts\n");
			return ret;
		}
	}

	/* Register the ring IRQ handlers and configure the rings */
	priv->ring = devm_kcalloc(dev, priv->config.rings,
				  sizeof(*priv->ring),
				  GFP_KERNEL);
	if (!priv->ring)
		return -ENOMEM;

	for (i = 0; i < priv->config.rings; i++) {
		char wq_name[9] = {0};
		int irq;
		struct safexcel_ring_irq_data *ring_irq;

		ret = safexcel_init_ring_descriptors(priv,
						     &priv->ring[i].cdr,
						     &priv->ring[i].rdr);
		if (ret) {
			dev_err(dev, "Failed to initialize rings\n");
			return ret;
		}

		priv->ring[i].rdr_req = devm_kcalloc(dev,
			EIP197_DEFAULT_RING_SIZE,
			sizeof(priv->ring[i].rdr_req),
			GFP_KERNEL);
		if (!priv->ring[i].rdr_req)
			return -ENOMEM;

		ring_irq = devm_kzalloc(dev, sizeof(*ring_irq), GFP_KERNEL);
		if (!ring_irq)
			return -ENOMEM;

		ring_irq->priv = priv;
		ring_irq->ring = i;

		irq = safexcel_request_ring_irq(pdev,
						EIP197_IRQ_NUMBER(i, is_pci_dev),
						is_pci_dev,
						safexcel_irq_ring,
						safexcel_irq_ring_thread,
						ring_irq);
		if (irq < 0) {
			dev_err(dev, "Failed to get IRQ ID for ring %d\n", i);
			return irq;
		}

		priv->ring[i].work_data.priv = priv;
		priv->ring[i].work_data.ring = i;
		INIT_WORK(&priv->ring[i].work_data.work,
			  safexcel_dequeue_work);

		snprintf(wq_name, 9, "wq_ring%d", i);
		priv->ring[i].workqueue =
			create_singlethread_workqueue(wq_name);
		if (!priv->ring[i].workqueue)
			return -ENOMEM;

		priv->ring[i].requests = 0;
		priv->ring[i].busy = false;

		crypto_init_queue(&priv->ring[i].queue,
				  EIP197_DEFAULT_RING_SIZE);

		spin_lock_init(&priv->ring[i].lock);
		spin_lock_init(&priv->ring[i].queue_lock);
	}

	atomic_set(&priv->ring_used, 0);

	ret = safexcel_hw_init(priv);
	if (ret) {
		dev_err(dev, "HW init failed (%d)\n", ret);
		return ret;
	}

	ret = safexcel_register_algorithms(priv);
	if (ret) {
		dev_err(dev, "Failed to register algorithms (%d)\n", ret);
		return ret;
	}

	return 0;
}