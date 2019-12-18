#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sahara_hw_link {int dummy; } ;
struct sahara_hw_desc {int dummy; } ;
struct sahara_dev {int version; void* clk_ipg; void* clk_ahb; void* kthread; int /*<<< orphan*/  dma_completion; int /*<<< orphan*/  queue_mutex; int /*<<< orphan*/  queue; void** hw_link; scalar_t__* hw_phys_link; void* context_base; scalar_t__ context_phys_base; scalar_t__ key_phys_base; scalar_t__ iv_phys_base; void* key_base; void* iv_base; scalar_t__* hw_phys_desc; void** hw_desc; void* regs_base; TYPE_1__* device; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int AES_KEYSIZE_128 ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int SAHARA_CMD_MODE_BATCH ; 
 int SAHARA_CMD_RESET ; 
 int SAHARA_CONTROL_ENABLE_INT ; 
 int SAHARA_CONTROL_RNG_AUTORSD ; 
 int SAHARA_CONTROL_SET_MAXBURST (int) ; 
 int SAHARA_CONTROL_SET_THROTTLE (int /*<<< orphan*/ ) ; 
 int SAHARA_MAX_HW_DESC ; 
 int SAHARA_MAX_HW_LINK ; 
 int /*<<< orphan*/  SAHARA_QUEUE_LENGTH ; 
 int /*<<< orphan*/  SAHARA_REG_CMD ; 
 int /*<<< orphan*/  SAHARA_REG_CONTROL ; 
 int /*<<< orphan*/  SAHARA_REG_VERSION ; 
 int SAHARA_VERSION_3 ; 
 int SAHARA_VERSION_4 ; 
 int SHA256_DIGEST_SIZE ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  crypto_init_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 struct sahara_dev* dev_ptr ; 
 void* devm_clk_get (TYPE_1__*,char*) ; 
 struct sahara_dev* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 void* devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sahara_dev*) ; 
 void* dmam_alloc_coherent (TYPE_1__*,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 void* kthread_run (int /*<<< orphan*/ ,struct sahara_dev*,char*) ; 
 int /*<<< orphan*/  kthread_stop (void*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sahara_dev*) ; 
 int /*<<< orphan*/  sahara_irq_handler ; 
 int /*<<< orphan*/  sahara_queue_manage ; 
 int sahara_read (struct sahara_dev*,int /*<<< orphan*/ ) ; 
 int sahara_register_algs (struct sahara_dev*) ; 
 int /*<<< orphan*/  sahara_write (struct sahara_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sahara_probe(struct platform_device *pdev)
{
	struct sahara_dev *dev;
	u32 version;
	int irq;
	int err;
	int i;

	dev = devm_kzalloc(&pdev->dev, sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	dev->device = &pdev->dev;
	platform_set_drvdata(pdev, dev);

	/* Get the base address */
	dev->regs_base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(dev->regs_base))
		return PTR_ERR(dev->regs_base);

	/* Get the IRQ */
	irq = platform_get_irq(pdev,  0);
	if (irq < 0)
		return irq;

	err = devm_request_irq(&pdev->dev, irq, sahara_irq_handler,
			       0, dev_name(&pdev->dev), dev);
	if (err) {
		dev_err(&pdev->dev, "failed to request irq\n");
		return err;
	}

	/* clocks */
	dev->clk_ipg = devm_clk_get(&pdev->dev, "ipg");
	if (IS_ERR(dev->clk_ipg)) {
		dev_err(&pdev->dev, "Could not get ipg clock\n");
		return PTR_ERR(dev->clk_ipg);
	}

	dev->clk_ahb = devm_clk_get(&pdev->dev, "ahb");
	if (IS_ERR(dev->clk_ahb)) {
		dev_err(&pdev->dev, "Could not get ahb clock\n");
		return PTR_ERR(dev->clk_ahb);
	}

	/* Allocate HW descriptors */
	dev->hw_desc[0] = dmam_alloc_coherent(&pdev->dev,
			SAHARA_MAX_HW_DESC * sizeof(struct sahara_hw_desc),
			&dev->hw_phys_desc[0], GFP_KERNEL);
	if (!dev->hw_desc[0]) {
		dev_err(&pdev->dev, "Could not allocate hw descriptors\n");
		return -ENOMEM;
	}
	dev->hw_desc[1] = dev->hw_desc[0] + 1;
	dev->hw_phys_desc[1] = dev->hw_phys_desc[0] +
				sizeof(struct sahara_hw_desc);

	/* Allocate space for iv and key */
	dev->key_base = dmam_alloc_coherent(&pdev->dev, 2 * AES_KEYSIZE_128,
				&dev->key_phys_base, GFP_KERNEL);
	if (!dev->key_base) {
		dev_err(&pdev->dev, "Could not allocate memory for key\n");
		return -ENOMEM;
	}
	dev->iv_base = dev->key_base + AES_KEYSIZE_128;
	dev->iv_phys_base = dev->key_phys_base + AES_KEYSIZE_128;

	/* Allocate space for context: largest digest + message length field */
	dev->context_base = dmam_alloc_coherent(&pdev->dev,
					SHA256_DIGEST_SIZE + 4,
					&dev->context_phys_base, GFP_KERNEL);
	if (!dev->context_base) {
		dev_err(&pdev->dev, "Could not allocate memory for MDHA context\n");
		return -ENOMEM;
	}

	/* Allocate space for HW links */
	dev->hw_link[0] = dmam_alloc_coherent(&pdev->dev,
			SAHARA_MAX_HW_LINK * sizeof(struct sahara_hw_link),
			&dev->hw_phys_link[0], GFP_KERNEL);
	if (!dev->hw_link[0]) {
		dev_err(&pdev->dev, "Could not allocate hw links\n");
		return -ENOMEM;
	}
	for (i = 1; i < SAHARA_MAX_HW_LINK; i++) {
		dev->hw_phys_link[i] = dev->hw_phys_link[i - 1] +
					sizeof(struct sahara_hw_link);
		dev->hw_link[i] = dev->hw_link[i - 1] + 1;
	}

	crypto_init_queue(&dev->queue, SAHARA_QUEUE_LENGTH);

	mutex_init(&dev->queue_mutex);

	dev_ptr = dev;

	dev->kthread = kthread_run(sahara_queue_manage, dev, "sahara_crypto");
	if (IS_ERR(dev->kthread)) {
		return PTR_ERR(dev->kthread);
	}

	init_completion(&dev->dma_completion);

	err = clk_prepare_enable(dev->clk_ipg);
	if (err)
		return err;
	err = clk_prepare_enable(dev->clk_ahb);
	if (err)
		goto clk_ipg_disable;

	version = sahara_read(dev, SAHARA_REG_VERSION);
	if (of_device_is_compatible(pdev->dev.of_node, "fsl,imx27-sahara")) {
		if (version != SAHARA_VERSION_3)
			err = -ENODEV;
	} else if (of_device_is_compatible(pdev->dev.of_node,
			"fsl,imx53-sahara")) {
		if (((version >> 8) & 0xff) != SAHARA_VERSION_4)
			err = -ENODEV;
		version = (version >> 8) & 0xff;
	}
	if (err == -ENODEV) {
		dev_err(&pdev->dev, "SAHARA version %d not supported\n",
				version);
		goto err_algs;
	}

	dev->version = version;

	sahara_write(dev, SAHARA_CMD_RESET | SAHARA_CMD_MODE_BATCH,
		     SAHARA_REG_CMD);
	sahara_write(dev, SAHARA_CONTROL_SET_THROTTLE(0) |
			SAHARA_CONTROL_SET_MAXBURST(8) |
			SAHARA_CONTROL_RNG_AUTORSD |
			SAHARA_CONTROL_ENABLE_INT,
			SAHARA_REG_CONTROL);

	err = sahara_register_algs(dev);
	if (err)
		goto err_algs;

	dev_info(&pdev->dev, "SAHARA version %d initialized\n", version);

	return 0;

err_algs:
	kthread_stop(dev->kthread);
	dev_ptr = NULL;
	clk_disable_unprepare(dev->clk_ahb);
clk_ipg_disable:
	clk_disable_unprepare(dev->clk_ipg);

	return err;
}