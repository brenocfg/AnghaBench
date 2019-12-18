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
struct resource {int /*<<< orphan*/  start; } ;
struct device {int /*<<< orphan*/  kobj; scalar_t__ of_node; } ;
struct platform_device {struct device dev; } ;
struct omap_sham_reqctx {int dummy; } ;
struct omap_sham_dev {int polling_mode; int /*<<< orphan*/  dma_lch; TYPE_3__* pdata; int /*<<< orphan*/  list; int /*<<< orphan*/  fallback_sz; int /*<<< orphan*/  flags; int /*<<< orphan*/  irq; int /*<<< orphan*/  phys_base; int /*<<< orphan*/  io_base; int /*<<< orphan*/  queue; int /*<<< orphan*/  done_task; int /*<<< orphan*/  lock; struct device* dev; } ;
struct TYPE_5__ {scalar_t__ statesize; } ;
struct ahash_alg {TYPE_1__ halg; int /*<<< orphan*/  import; int /*<<< orphan*/  export; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev_list; } ;
struct TYPE_7__ {int major_mask; int major_shift; int minor_mask; int minor_shift; int algs_info_size; TYPE_2__* algs_info; int /*<<< orphan*/  flags; int /*<<< orphan*/  intr_hdlr; } ;
struct TYPE_6__ {int size; int registered; struct ahash_alg* algs_list; } ;

/* Variables and functions */
 scalar_t__ BUFLEN ; 
 int /*<<< orphan*/  DEFAULT_AUTOSUSPEND_DELAY ; 
 int /*<<< orphan*/  DMA_SLAVE ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IRQF_TRIGGER_NONE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OMAP_SHAM_QUEUE_LENGTH ; 
 int /*<<< orphan*/  OMAP_SHA_DMA_THRESHOLD ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA_REG_REV (struct omap_sham_dev*) ; 
 int /*<<< orphan*/  crypto_init_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int crypto_register_ahash (struct ahash_alg*) ; 
 int /*<<< orphan*/  crypto_unregister_ahash (struct ahash_alg*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct omap_sham_dev* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct omap_sham_dev*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_request_chan (struct device*,char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_sham_attr_group ; 
 int /*<<< orphan*/  omap_sham_done_task ; 
 int /*<<< orphan*/  omap_sham_export ; 
 int omap_sham_get_res_of (struct omap_sham_dev*,struct device*,struct resource*) ; 
 int omap_sham_get_res_pdev (struct omap_sham_dev*,struct platform_device*,struct resource*) ; 
 int /*<<< orphan*/  omap_sham_import ; 
 int omap_sham_read (struct omap_sham_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct omap_sham_dev*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_irq_safe (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 
 TYPE_4__ sham ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int omap_sham_probe(struct platform_device *pdev)
{
	struct omap_sham_dev *dd;
	struct device *dev = &pdev->dev;
	struct resource res;
	dma_cap_mask_t mask;
	int err, i, j;
	u32 rev;

	dd = devm_kzalloc(dev, sizeof(struct omap_sham_dev), GFP_KERNEL);
	if (dd == NULL) {
		dev_err(dev, "unable to alloc data struct.\n");
		err = -ENOMEM;
		goto data_err;
	}
	dd->dev = dev;
	platform_set_drvdata(pdev, dd);

	INIT_LIST_HEAD(&dd->list);
	spin_lock_init(&dd->lock);
	tasklet_init(&dd->done_task, omap_sham_done_task, (unsigned long)dd);
	crypto_init_queue(&dd->queue, OMAP_SHAM_QUEUE_LENGTH);

	err = (dev->of_node) ? omap_sham_get_res_of(dd, dev, &res) :
			       omap_sham_get_res_pdev(dd, pdev, &res);
	if (err)
		goto data_err;

	dd->io_base = devm_ioremap_resource(dev, &res);
	if (IS_ERR(dd->io_base)) {
		err = PTR_ERR(dd->io_base);
		goto data_err;
	}
	dd->phys_base = res.start;

	err = devm_request_irq(dev, dd->irq, dd->pdata->intr_hdlr,
			       IRQF_TRIGGER_NONE, dev_name(dev), dd);
	if (err) {
		dev_err(dev, "unable to request irq %d, err = %d\n",
			dd->irq, err);
		goto data_err;
	}

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	dd->dma_lch = dma_request_chan(dev, "rx");
	if (IS_ERR(dd->dma_lch)) {
		err = PTR_ERR(dd->dma_lch);
		if (err == -EPROBE_DEFER)
			goto data_err;

		dd->polling_mode = 1;
		dev_dbg(dev, "using polling mode instead of dma\n");
	}

	dd->flags |= dd->pdata->flags;

	pm_runtime_use_autosuspend(dev);
	pm_runtime_set_autosuspend_delay(dev, DEFAULT_AUTOSUSPEND_DELAY);

	dd->fallback_sz = OMAP_SHA_DMA_THRESHOLD;

	pm_runtime_enable(dev);
	pm_runtime_irq_safe(dev);

	err = pm_runtime_get_sync(dev);
	if (err < 0) {
		dev_err(dev, "failed to get sync: %d\n", err);
		goto err_pm;
	}

	rev = omap_sham_read(dd, SHA_REG_REV(dd));
	pm_runtime_put_sync(&pdev->dev);

	dev_info(dev, "hw accel on OMAP rev %u.%u\n",
		(rev & dd->pdata->major_mask) >> dd->pdata->major_shift,
		(rev & dd->pdata->minor_mask) >> dd->pdata->minor_shift);

	spin_lock(&sham.lock);
	list_add_tail(&dd->list, &sham.dev_list);
	spin_unlock(&sham.lock);

	for (i = 0; i < dd->pdata->algs_info_size; i++) {
		for (j = 0; j < dd->pdata->algs_info[i].size; j++) {
			struct ahash_alg *alg;

			alg = &dd->pdata->algs_info[i].algs_list[j];
			alg->export = omap_sham_export;
			alg->import = omap_sham_import;
			alg->halg.statesize = sizeof(struct omap_sham_reqctx) +
					      BUFLEN;
			err = crypto_register_ahash(alg);
			if (err)
				goto err_algs;

			dd->pdata->algs_info[i].registered++;
		}
	}

	err = sysfs_create_group(&dev->kobj, &omap_sham_attr_group);
	if (err) {
		dev_err(dev, "could not create sysfs device attrs\n");
		goto err_algs;
	}

	return 0;

err_algs:
	for (i = dd->pdata->algs_info_size - 1; i >= 0; i--)
		for (j = dd->pdata->algs_info[i].registered - 1; j >= 0; j--)
			crypto_unregister_ahash(
					&dd->pdata->algs_info[i].algs_list[j]);
err_pm:
	pm_runtime_disable(dev);
	if (!dd->polling_mode)
		dma_release_channel(dd->dma_lch);
data_err:
	dev_err(dev, "initialization failed.\n");

	return err;
}