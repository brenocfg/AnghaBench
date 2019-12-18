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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct adc_jack_pdata {int /*<<< orphan*/  name; int /*<<< orphan*/  irq_flags; scalar_t__ wakeup_source; int /*<<< orphan*/  handling_delay_ms; int /*<<< orphan*/  consumer_channel; TYPE_1__* adc_conditions; int /*<<< orphan*/  cable_names; } ;
struct TYPE_4__ {int /*<<< orphan*/  work; } ;
struct adc_jack_data {int num_conditions; scalar_t__ irq; TYPE_2__ handler; scalar_t__ wakeup_source; int /*<<< orphan*/  edev; int /*<<< orphan*/  handling_delay; int /*<<< orphan*/  chan; TYPE_1__* adc_conditions; int /*<<< orphan*/ * dev; } ;
struct TYPE_3__ {scalar_t__ id; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ EXTCON_NONE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DEFERRABLE_WORK (TYPE_2__*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *)) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adc_jack_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adc_jack_irq_thread ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct adc_jack_pdata* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  devm_extcon_dev_allocate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int devm_extcon_dev_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct adc_jack_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_channel_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct adc_jack_data*) ; 
 int request_any_context_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct adc_jack_data*) ; 

__attribute__((used)) static int adc_jack_probe(struct platform_device *pdev)
{
	struct adc_jack_data *data;
	struct adc_jack_pdata *pdata = dev_get_platdata(&pdev->dev);
	int i, err = 0;

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	if (!pdata->cable_names) {
		dev_err(&pdev->dev, "error: cable_names not defined.\n");
		return -EINVAL;
	}

	data->dev = &pdev->dev;
	data->edev = devm_extcon_dev_allocate(&pdev->dev, pdata->cable_names);
	if (IS_ERR(data->edev)) {
		dev_err(&pdev->dev, "failed to allocate extcon device\n");
		return -ENOMEM;
	}

	if (!pdata->adc_conditions) {
		dev_err(&pdev->dev, "error: adc_conditions not defined.\n");
		return -EINVAL;
	}
	data->adc_conditions = pdata->adc_conditions;

	/* Check the length of array and set num_conditions */
	for (i = 0; data->adc_conditions[i].id != EXTCON_NONE; i++);
	data->num_conditions = i;

	data->chan = iio_channel_get(&pdev->dev, pdata->consumer_channel);
	if (IS_ERR(data->chan))
		return PTR_ERR(data->chan);

	data->handling_delay = msecs_to_jiffies(pdata->handling_delay_ms);
	data->wakeup_source = pdata->wakeup_source;

	INIT_DEFERRABLE_WORK(&data->handler, adc_jack_handler);

	platform_set_drvdata(pdev, data);

	err = devm_extcon_dev_register(&pdev->dev, data->edev);
	if (err)
		return err;

	data->irq = platform_get_irq(pdev, 0);
	if (data->irq < 0)
		return -ENODEV;

	err = request_any_context_irq(data->irq, adc_jack_irq_thread,
			pdata->irq_flags, pdata->name, data);

	if (err < 0) {
		dev_err(&pdev->dev, "error: irq %d\n", data->irq);
		return err;
	}

	if (data->wakeup_source)
		device_init_wakeup(&pdev->dev, 1);

	adc_jack_handler(&data->handler.work);
	return 0;
}