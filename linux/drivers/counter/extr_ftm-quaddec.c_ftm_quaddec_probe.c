#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_8__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_9__ {int num_counts; struct ftm_quaddec* priv; int /*<<< orphan*/  num_signals; int /*<<< orphan*/  signals; int /*<<< orphan*/ * counts; int /*<<< orphan*/ * ops; TYPE_1__* parent; int /*<<< orphan*/  name; } ;
struct ftm_quaddec {TYPE_4__ counter; int /*<<< orphan*/  ftm_quaddec_mutex; int /*<<< orphan*/  ftm_base; int /*<<< orphan*/  big_endian; struct platform_device* pdev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int devm_add_action_or_reset (TYPE_1__*,int /*<<< orphan*/ ,struct ftm_quaddec*) ; 
 int devm_counter_register (TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  devm_ioremap (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ftm_quaddec* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftm_quaddec_cnt_ops ; 
 int /*<<< orphan*/  ftm_quaddec_counts ; 
 int /*<<< orphan*/  ftm_quaddec_disable ; 
 int /*<<< orphan*/  ftm_quaddec_init (struct ftm_quaddec*) ; 
 int /*<<< orphan*/  ftm_quaddec_signals ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ftm_quaddec*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int ftm_quaddec_probe(struct platform_device *pdev)
{
	struct ftm_quaddec *ftm;

	struct device_node *node = pdev->dev.of_node;
	struct resource *io;
	int ret;

	ftm = devm_kzalloc(&pdev->dev, sizeof(*ftm), GFP_KERNEL);
	if (!ftm)
		return -ENOMEM;

	platform_set_drvdata(pdev, ftm);

	io = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!io) {
		dev_err(&pdev->dev, "Failed to get memory region\n");
		return -ENODEV;
	}

	ftm->pdev = pdev;
	ftm->big_endian = of_property_read_bool(node, "big-endian");
	ftm->ftm_base = devm_ioremap(&pdev->dev, io->start, resource_size(io));

	if (!ftm->ftm_base) {
		dev_err(&pdev->dev, "Failed to map memory region\n");
		return -EINVAL;
	}
	ftm->counter.name = dev_name(&pdev->dev);
	ftm->counter.parent = &pdev->dev;
	ftm->counter.ops = &ftm_quaddec_cnt_ops;
	ftm->counter.counts = &ftm_quaddec_counts;
	ftm->counter.num_counts = 1;
	ftm->counter.signals = ftm_quaddec_signals;
	ftm->counter.num_signals = ARRAY_SIZE(ftm_quaddec_signals);
	ftm->counter.priv = ftm;

	mutex_init(&ftm->ftm_quaddec_mutex);

	ftm_quaddec_init(ftm);

	ret = devm_add_action_or_reset(&pdev->dev, ftm_quaddec_disable, ftm);
	if (ret)
		return ret;

	ret = devm_counter_register(&pdev->dev, &ftm->counter);
	if (ret)
		return ret;

	return 0;
}