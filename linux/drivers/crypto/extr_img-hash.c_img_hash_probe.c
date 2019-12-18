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
struct resource {int /*<<< orphan*/  start; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct img_hash_dev {int /*<<< orphan*/  dma_task; int /*<<< orphan*/  done_task; void* hash_clk; void* sys_clk; int /*<<< orphan*/  dma_lch; int /*<<< orphan*/  list; int /*<<< orphan*/  bus_addr; void* cpu_addr; void* io_base; int /*<<< orphan*/  queue; struct device* dev; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IMG_HASH_QUEUE_LENGTH ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  crypto_init_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct img_hash_dev* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct img_hash_dev*) ; 
 int dma_chan_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 TYPE_1__ img_hash ; 
 int img_hash_dma_init (struct img_hash_dev*) ; 
 int /*<<< orphan*/  img_hash_dma_task ; 
 int /*<<< orphan*/  img_hash_done_task ; 
 int /*<<< orphan*/  img_irq_handler ; 
 int img_register_algs (struct img_hash_dev*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct img_hash_dev*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int img_hash_probe(struct platform_device *pdev)
{
	struct img_hash_dev *hdev;
	struct device *dev = &pdev->dev;
	struct resource *hash_res;
	int	irq;
	int err;

	hdev = devm_kzalloc(dev, sizeof(*hdev), GFP_KERNEL);
	if (hdev == NULL)
		return -ENOMEM;

	spin_lock_init(&hdev->lock);

	hdev->dev = dev;

	platform_set_drvdata(pdev, hdev);

	INIT_LIST_HEAD(&hdev->list);

	tasklet_init(&hdev->done_task, img_hash_done_task, (unsigned long)hdev);
	tasklet_init(&hdev->dma_task, img_hash_dma_task, (unsigned long)hdev);

	crypto_init_queue(&hdev->queue, IMG_HASH_QUEUE_LENGTH);

	/* Register bank */
	hdev->io_base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(hdev->io_base)) {
		err = PTR_ERR(hdev->io_base);
		dev_err(dev, "can't ioremap, returned %d\n", err);

		goto res_err;
	}

	/* Write port (DMA or CPU) */
	hash_res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	hdev->cpu_addr = devm_ioremap_resource(dev, hash_res);
	if (IS_ERR(hdev->cpu_addr)) {
		dev_err(dev, "can't ioremap write port\n");
		err = PTR_ERR(hdev->cpu_addr);
		goto res_err;
	}
	hdev->bus_addr = hash_res->start;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		err = irq;
		goto res_err;
	}

	err = devm_request_irq(dev, irq, img_irq_handler, 0,
			       dev_name(dev), hdev);
	if (err) {
		dev_err(dev, "unable to request irq\n");
		goto res_err;
	}
	dev_dbg(dev, "using IRQ channel %d\n", irq);

	hdev->hash_clk = devm_clk_get(&pdev->dev, "hash");
	if (IS_ERR(hdev->hash_clk)) {
		dev_err(dev, "clock initialization failed.\n");
		err = PTR_ERR(hdev->hash_clk);
		goto res_err;
	}

	hdev->sys_clk = devm_clk_get(&pdev->dev, "sys");
	if (IS_ERR(hdev->sys_clk)) {
		dev_err(dev, "clock initialization failed.\n");
		err = PTR_ERR(hdev->sys_clk);
		goto res_err;
	}

	err = clk_prepare_enable(hdev->hash_clk);
	if (err)
		goto res_err;

	err = clk_prepare_enable(hdev->sys_clk);
	if (err)
		goto clk_err;

	err = img_hash_dma_init(hdev);
	if (err)
		goto dma_err;

	dev_dbg(dev, "using %s for DMA transfers\n",
		dma_chan_name(hdev->dma_lch));

	spin_lock(&img_hash.lock);
	list_add_tail(&hdev->list, &img_hash.dev_list);
	spin_unlock(&img_hash.lock);

	err = img_register_algs(hdev);
	if (err)
		goto err_algs;
	dev_info(dev, "Img MD5/SHA1/SHA224/SHA256 Hardware accelerator initialized\n");

	return 0;

err_algs:
	spin_lock(&img_hash.lock);
	list_del(&hdev->list);
	spin_unlock(&img_hash.lock);
	dma_release_channel(hdev->dma_lch);
dma_err:
	clk_disable_unprepare(hdev->sys_clk);
clk_err:
	clk_disable_unprepare(hdev->hash_clk);
res_err:
	tasklet_kill(&hdev->done_task);
	tasklet_kill(&hdev->dma_task);

	return err;
}