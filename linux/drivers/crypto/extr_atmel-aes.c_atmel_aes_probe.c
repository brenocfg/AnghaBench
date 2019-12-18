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
struct resource {int /*<<< orphan*/  start; } ;
struct device {struct crypto_platform_data* platform_data; } ;
struct platform_device {struct device dev; } ;
struct crypto_platform_data {int /*<<< orphan*/  dma_slave; } ;
struct TYPE_7__ {int /*<<< orphan*/  chan; } ;
struct TYPE_6__ {int /*<<< orphan*/  chan; } ;
struct TYPE_5__ {scalar_t__ has_authenc; } ;
struct atmel_aes_dev {int irq; int /*<<< orphan*/  queue_task; int /*<<< orphan*/  done_task; struct crypto_platform_data* iclk; int /*<<< orphan*/  list; TYPE_3__ dst; TYPE_2__ src; TYPE_1__ caps; struct crypto_platform_data* io_base; int /*<<< orphan*/  phys_base; int /*<<< orphan*/  queue; int /*<<< orphan*/  lock; struct device* dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_AES_QUEUE_LENGTH ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (struct crypto_platform_data*) ; 
 int PTR_ERR (struct crypto_platform_data*) ; 
 TYPE_4__ atmel_aes ; 
 int /*<<< orphan*/  atmel_aes_buff_cleanup (struct atmel_aes_dev*) ; 
 int atmel_aes_buff_init (struct atmel_aes_dev*) ; 
 int /*<<< orphan*/  atmel_aes_dma_cleanup (struct atmel_aes_dev*) ; 
 int atmel_aes_dma_init (struct atmel_aes_dev*,struct crypto_platform_data*) ; 
 int /*<<< orphan*/  atmel_aes_done_task ; 
 int /*<<< orphan*/  atmel_aes_get_cap (struct atmel_aes_dev*) ; 
 int atmel_aes_hw_version_init (struct atmel_aes_dev*) ; 
 int /*<<< orphan*/  atmel_aes_irq ; 
 struct crypto_platform_data* atmel_aes_of_init (struct platform_device*) ; 
 int /*<<< orphan*/  atmel_aes_queue_task ; 
 int atmel_aes_register_algs (struct atmel_aes_dev*) ; 
 int /*<<< orphan*/  atmel_sha_authenc_is_ready () ; 
 int clk_prepare (struct crypto_platform_data*) ; 
 int /*<<< orphan*/  clk_unprepare (struct crypto_platform_data*) ; 
 int /*<<< orphan*/  crypto_init_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct crypto_platform_data* devm_clk_get (struct device*,char*) ; 
 struct crypto_platform_data* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct atmel_aes_dev* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct atmel_aes_dev*) ; 
 int /*<<< orphan*/  dma_chan_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct atmel_aes_dev*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atmel_aes_probe(struct platform_device *pdev)
{
	struct atmel_aes_dev *aes_dd;
	struct crypto_platform_data *pdata;
	struct device *dev = &pdev->dev;
	struct resource *aes_res;
	int err;

	pdata = pdev->dev.platform_data;
	if (!pdata) {
		pdata = atmel_aes_of_init(pdev);
		if (IS_ERR(pdata)) {
			err = PTR_ERR(pdata);
			goto aes_dd_err;
		}
	}

	if (!pdata->dma_slave) {
		err = -ENXIO;
		goto aes_dd_err;
	}

	aes_dd = devm_kzalloc(&pdev->dev, sizeof(*aes_dd), GFP_KERNEL);
	if (aes_dd == NULL) {
		err = -ENOMEM;
		goto aes_dd_err;
	}

	aes_dd->dev = dev;

	platform_set_drvdata(pdev, aes_dd);

	INIT_LIST_HEAD(&aes_dd->list);
	spin_lock_init(&aes_dd->lock);

	tasklet_init(&aes_dd->done_task, atmel_aes_done_task,
					(unsigned long)aes_dd);
	tasklet_init(&aes_dd->queue_task, atmel_aes_queue_task,
					(unsigned long)aes_dd);

	crypto_init_queue(&aes_dd->queue, ATMEL_AES_QUEUE_LENGTH);

	/* Get the base address */
	aes_res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!aes_res) {
		dev_err(dev, "no MEM resource info\n");
		err = -ENODEV;
		goto res_err;
	}
	aes_dd->phys_base = aes_res->start;

	/* Get the IRQ */
	aes_dd->irq = platform_get_irq(pdev,  0);
	if (aes_dd->irq < 0) {
		err = aes_dd->irq;
		goto res_err;
	}

	err = devm_request_irq(&pdev->dev, aes_dd->irq, atmel_aes_irq,
			       IRQF_SHARED, "atmel-aes", aes_dd);
	if (err) {
		dev_err(dev, "unable to request aes irq.\n");
		goto res_err;
	}

	/* Initializing the clock */
	aes_dd->iclk = devm_clk_get(&pdev->dev, "aes_clk");
	if (IS_ERR(aes_dd->iclk)) {
		dev_err(dev, "clock initialization failed.\n");
		err = PTR_ERR(aes_dd->iclk);
		goto res_err;
	}

	aes_dd->io_base = devm_ioremap_resource(&pdev->dev, aes_res);
	if (IS_ERR(aes_dd->io_base)) {
		dev_err(dev, "can't ioremap\n");
		err = PTR_ERR(aes_dd->io_base);
		goto res_err;
	}

	err = clk_prepare(aes_dd->iclk);
	if (err)
		goto res_err;

	err = atmel_aes_hw_version_init(aes_dd);
	if (err)
		goto iclk_unprepare;

	atmel_aes_get_cap(aes_dd);

#ifdef CONFIG_CRYPTO_DEV_ATMEL_AUTHENC
	if (aes_dd->caps.has_authenc && !atmel_sha_authenc_is_ready()) {
		err = -EPROBE_DEFER;
		goto iclk_unprepare;
	}
#endif

	err = atmel_aes_buff_init(aes_dd);
	if (err)
		goto err_aes_buff;

	err = atmel_aes_dma_init(aes_dd, pdata);
	if (err)
		goto err_aes_dma;

	spin_lock(&atmel_aes.lock);
	list_add_tail(&aes_dd->list, &atmel_aes.dev_list);
	spin_unlock(&atmel_aes.lock);

	err = atmel_aes_register_algs(aes_dd);
	if (err)
		goto err_algs;

	dev_info(dev, "Atmel AES - Using %s, %s for DMA transfers\n",
			dma_chan_name(aes_dd->src.chan),
			dma_chan_name(aes_dd->dst.chan));

	return 0;

err_algs:
	spin_lock(&atmel_aes.lock);
	list_del(&aes_dd->list);
	spin_unlock(&atmel_aes.lock);
	atmel_aes_dma_cleanup(aes_dd);
err_aes_dma:
	atmel_aes_buff_cleanup(aes_dd);
err_aes_buff:
iclk_unprepare:
	clk_unprepare(aes_dd->iclk);
res_err:
	tasklet_kill(&aes_dd->done_task);
	tasklet_kill(&aes_dd->queue_task);
aes_dd_err:
	if (err != -EPROBE_DEFER)
		dev_err(dev, "initialization failed.\n");

	return err;
}