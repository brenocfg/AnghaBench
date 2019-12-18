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
typedef  int /*<<< orphan*/  svc_invoke_fn ;
struct stratix10_svc_sh_memory {int /*<<< orphan*/ * invoke_fn; } ;
struct stratix10_svc_data {int dummy; } ;
struct stratix10_svc_controller {int /*<<< orphan*/  node; int /*<<< orphan*/  svc_fifo_lock; int /*<<< orphan*/  svc_fifo; int /*<<< orphan*/  complete_status; int /*<<< orphan*/ * invoke_fn; int /*<<< orphan*/ * task; struct gen_pool* genpool; struct stratix10_svc_chan* chans; scalar_t__ num_active_client; int /*<<< orphan*/  num_chans; struct device* dev; } ;
struct stratix10_svc_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  name; struct stratix10_svc_controller* ctrl; int /*<<< orphan*/ * scl; } ;
struct stratix10_svc {int /*<<< orphan*/  stratix10_svc_rsu; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct gen_pool {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STRATIX10_RSU ; 
 int /*<<< orphan*/  SVC_CLIENT_FPGA ; 
 int /*<<< orphan*/  SVC_CLIENT_RSU ; 
 int /*<<< orphan*/  SVC_NUM_CHANNEL ; 
 int SVC_NUM_DATA_IN_FIFO ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct stratix10_svc*) ; 
 struct stratix10_svc_chan* devm_kmalloc_array (struct device*,int /*<<< orphan*/ ,int,int) ; 
 void* devm_kzalloc (struct device*,int,int) ; 
 int /*<<< orphan*/ * get_invoke_func (struct device*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int kfifo_alloc (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int platform_device_add (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct stratix10_svc_controller*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct gen_pool* svc_create_memory_pool (struct platform_device*,struct stratix10_svc_sh_memory*) ; 
 int /*<<< orphan*/  svc_ctrl ; 
 int svc_get_sh_memory (struct platform_device*,struct stratix10_svc_sh_memory*) ; 

__attribute__((used)) static int stratix10_svc_drv_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct stratix10_svc_controller *controller;
	struct stratix10_svc_chan *chans;
	struct gen_pool *genpool;
	struct stratix10_svc_sh_memory *sh_memory;
	struct stratix10_svc *svc;

	svc_invoke_fn *invoke_fn;
	size_t fifo_size;
	int ret;

	/* get SMC or HVC function */
	invoke_fn = get_invoke_func(dev);
	if (IS_ERR(invoke_fn))
		return -EINVAL;

	sh_memory = devm_kzalloc(dev, sizeof(*sh_memory), GFP_KERNEL);
	if (!sh_memory)
		return -ENOMEM;

	sh_memory->invoke_fn = invoke_fn;
	ret = svc_get_sh_memory(pdev, sh_memory);
	if (ret)
		return ret;

	genpool = svc_create_memory_pool(pdev, sh_memory);
	if (!genpool)
		return -ENOMEM;

	/* allocate service controller and supporting channel */
	controller = devm_kzalloc(dev, sizeof(*controller), GFP_KERNEL);
	if (!controller)
		return -ENOMEM;

	chans = devm_kmalloc_array(dev, SVC_NUM_CHANNEL,
				   sizeof(*chans), GFP_KERNEL | __GFP_ZERO);
	if (!chans)
		return -ENOMEM;

	controller->dev = dev;
	controller->num_chans = SVC_NUM_CHANNEL;
	controller->num_active_client = 0;
	controller->chans = chans;
	controller->genpool = genpool;
	controller->task = NULL;
	controller->invoke_fn = invoke_fn;
	init_completion(&controller->complete_status);

	fifo_size = sizeof(struct stratix10_svc_data) * SVC_NUM_DATA_IN_FIFO;
	ret = kfifo_alloc(&controller->svc_fifo, fifo_size, GFP_KERNEL);
	if (ret) {
		dev_err(dev, "failed to allocate FIFO\n");
		return ret;
	}
	spin_lock_init(&controller->svc_fifo_lock);

	chans[0].scl = NULL;
	chans[0].ctrl = controller;
	chans[0].name = SVC_CLIENT_FPGA;
	spin_lock_init(&chans[0].lock);

	chans[1].scl = NULL;
	chans[1].ctrl = controller;
	chans[1].name = SVC_CLIENT_RSU;
	spin_lock_init(&chans[1].lock);

	list_add_tail(&controller->node, &svc_ctrl);
	platform_set_drvdata(pdev, controller);

	/* add svc client device(s) */
	svc = devm_kzalloc(dev, sizeof(*svc), GFP_KERNEL);
	if (!svc)
		return -ENOMEM;

	svc->stratix10_svc_rsu = platform_device_alloc(STRATIX10_RSU, 0);
	if (!svc->stratix10_svc_rsu) {
		dev_err(dev, "failed to allocate %s device\n", STRATIX10_RSU);
		return -ENOMEM;
	}

	ret = platform_device_add(svc->stratix10_svc_rsu);
	if (ret) {
		platform_device_put(svc->stratix10_svc_rsu);
		return ret;
	}
	dev_set_drvdata(dev, svc);

	pr_info("Intel Service Layer Driver Initialized\n");

	return ret;
}