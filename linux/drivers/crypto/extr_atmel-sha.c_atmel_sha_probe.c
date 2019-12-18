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
struct resource {int /*<<< orphan*/  start; } ;
struct device {struct crypto_platform_data* platform_data; } ;
struct platform_device {struct device dev; } ;
struct crypto_platform_data {int /*<<< orphan*/  dma_slave; } ;
struct TYPE_5__ {scalar_t__ has_dma; scalar_t__ has_sha_384_512; scalar_t__ has_sha224; } ;
struct TYPE_4__ {int /*<<< orphan*/  chan; } ;
struct atmel_sha_dev {int irq; int /*<<< orphan*/  done_task; int /*<<< orphan*/  queue_task; struct crypto_platform_data* iclk; TYPE_2__ caps; int /*<<< orphan*/  list; TYPE_1__ dma_lch_in; struct crypto_platform_data* io_base; int /*<<< orphan*/  phys_base; int /*<<< orphan*/  queue; int /*<<< orphan*/  lock; struct device* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_SHA_QUEUE_LENGTH ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (struct crypto_platform_data*) ; 
 int PTR_ERR (struct crypto_platform_data*) ; 
 TYPE_3__ atmel_sha ; 
 int /*<<< orphan*/  atmel_sha_dma_cleanup (struct atmel_sha_dev*) ; 
 int atmel_sha_dma_init (struct atmel_sha_dev*,struct crypto_platform_data*) ; 
 int /*<<< orphan*/  atmel_sha_done_task ; 
 int /*<<< orphan*/  atmel_sha_get_cap (struct atmel_sha_dev*) ; 
 int /*<<< orphan*/  atmel_sha_hw_version_init (struct atmel_sha_dev*) ; 
 int /*<<< orphan*/  atmel_sha_irq ; 
 struct crypto_platform_data* atmel_sha_of_init (struct platform_device*) ; 
 int /*<<< orphan*/  atmel_sha_queue_task ; 
 int atmel_sha_register_algs (struct atmel_sha_dev*) ; 
 int clk_prepare (struct crypto_platform_data*) ; 
 int /*<<< orphan*/  clk_unprepare (struct crypto_platform_data*) ; 
 int /*<<< orphan*/  crypto_init_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char*,...) ; 
 struct crypto_platform_data* devm_clk_get (struct device*,char*) ; 
 struct crypto_platform_data* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct atmel_sha_dev* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct atmel_sha_dev*) ; 
 int /*<<< orphan*/  dma_chan_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct atmel_sha_dev*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atmel_sha_probe(struct platform_device *pdev)
{
	struct atmel_sha_dev *sha_dd;
	struct crypto_platform_data	*pdata;
	struct device *dev = &pdev->dev;
	struct resource *sha_res;
	int err;

	sha_dd = devm_kzalloc(&pdev->dev, sizeof(*sha_dd), GFP_KERNEL);
	if (sha_dd == NULL) {
		err = -ENOMEM;
		goto sha_dd_err;
	}

	sha_dd->dev = dev;

	platform_set_drvdata(pdev, sha_dd);

	INIT_LIST_HEAD(&sha_dd->list);
	spin_lock_init(&sha_dd->lock);

	tasklet_init(&sha_dd->done_task, atmel_sha_done_task,
					(unsigned long)sha_dd);
	tasklet_init(&sha_dd->queue_task, atmel_sha_queue_task,
					(unsigned long)sha_dd);

	crypto_init_queue(&sha_dd->queue, ATMEL_SHA_QUEUE_LENGTH);

	/* Get the base address */
	sha_res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!sha_res) {
		dev_err(dev, "no MEM resource info\n");
		err = -ENODEV;
		goto res_err;
	}
	sha_dd->phys_base = sha_res->start;

	/* Get the IRQ */
	sha_dd->irq = platform_get_irq(pdev,  0);
	if (sha_dd->irq < 0) {
		err = sha_dd->irq;
		goto res_err;
	}

	err = devm_request_irq(&pdev->dev, sha_dd->irq, atmel_sha_irq,
			       IRQF_SHARED, "atmel-sha", sha_dd);
	if (err) {
		dev_err(dev, "unable to request sha irq.\n");
		goto res_err;
	}

	/* Initializing the clock */
	sha_dd->iclk = devm_clk_get(&pdev->dev, "sha_clk");
	if (IS_ERR(sha_dd->iclk)) {
		dev_err(dev, "clock initialization failed.\n");
		err = PTR_ERR(sha_dd->iclk);
		goto res_err;
	}

	sha_dd->io_base = devm_ioremap_resource(&pdev->dev, sha_res);
	if (IS_ERR(sha_dd->io_base)) {
		dev_err(dev, "can't ioremap\n");
		err = PTR_ERR(sha_dd->io_base);
		goto res_err;
	}

	err = clk_prepare(sha_dd->iclk);
	if (err)
		goto res_err;

	atmel_sha_hw_version_init(sha_dd);

	atmel_sha_get_cap(sha_dd);

	if (sha_dd->caps.has_dma) {
		pdata = pdev->dev.platform_data;
		if (!pdata) {
			pdata = atmel_sha_of_init(pdev);
			if (IS_ERR(pdata)) {
				dev_err(&pdev->dev, "platform data not available\n");
				err = PTR_ERR(pdata);
				goto iclk_unprepare;
			}
		}
		if (!pdata->dma_slave) {
			err = -ENXIO;
			goto iclk_unprepare;
		}
		err = atmel_sha_dma_init(sha_dd, pdata);
		if (err)
			goto err_sha_dma;

		dev_info(dev, "using %s for DMA transfers\n",
				dma_chan_name(sha_dd->dma_lch_in.chan));
	}

	spin_lock(&atmel_sha.lock);
	list_add_tail(&sha_dd->list, &atmel_sha.dev_list);
	spin_unlock(&atmel_sha.lock);

	err = atmel_sha_register_algs(sha_dd);
	if (err)
		goto err_algs;

	dev_info(dev, "Atmel SHA1/SHA256%s%s\n",
			sha_dd->caps.has_sha224 ? "/SHA224" : "",
			sha_dd->caps.has_sha_384_512 ? "/SHA384/SHA512" : "");

	return 0;

err_algs:
	spin_lock(&atmel_sha.lock);
	list_del(&sha_dd->list);
	spin_unlock(&atmel_sha.lock);
	if (sha_dd->caps.has_dma)
		atmel_sha_dma_cleanup(sha_dd);
err_sha_dma:
iclk_unprepare:
	clk_unprepare(sha_dd->iclk);
res_err:
	tasklet_kill(&sha_dd->queue_task);
	tasklet_kill(&sha_dd->done_task);
sha_dd_err:
	dev_err(dev, "initialization failed.\n");

	return err;
}