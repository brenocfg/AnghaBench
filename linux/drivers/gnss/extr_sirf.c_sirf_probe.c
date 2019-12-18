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
struct sirf_data {int active; int irq; struct gnss_device* gdev; void* vcc; void* on_off; void* wakeup; void* lna; int /*<<< orphan*/  power_wait; int /*<<< orphan*/  serdev_mutex; int /*<<< orphan*/  gdev_mutex; struct serdev_device* serdev; } ;
struct device {int dummy; } ;
struct serdev_device {struct device dev; } ;
struct gnss_device {int /*<<< orphan*/ * ops; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GNSS_TYPE_SIRF ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  SIRF_BOOT_DELAY ; 
 int /*<<< orphan*/  SIRF_REPORT_CYCLE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 void* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct sirf_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_regulator_get (struct device*,char*) ; 
 int /*<<< orphan*/  free_irq (int,struct sirf_data*) ; 
 struct gnss_device* gnss_allocate_device (struct device*) ; 
 int /*<<< orphan*/  gnss_put_device (struct gnss_device*) ; 
 int gnss_register_device (struct gnss_device*) ; 
 int /*<<< orphan*/  gnss_set_drvdata (struct gnss_device*,struct sirf_data*) ; 
 int gpiod_get_value_cansleep (void*) ; 
 int gpiod_to_irq (void*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (struct device*) ; 
 int /*<<< orphan*/  regulator_disable (void*) ; 
 int regulator_enable (void*) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct sirf_data*) ; 
 int /*<<< orphan*/  serdev_device_set_client_ops (struct serdev_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serdev_device_set_drvdata (struct serdev_device*,struct sirf_data*) ; 
 int /*<<< orphan*/  sirf_gnss_ops ; 
 int sirf_parse_dt (struct serdev_device*) ; 
 int sirf_runtime_resume (struct device*) ; 
 int /*<<< orphan*/  sirf_runtime_suspend (struct device*) ; 
 int /*<<< orphan*/  sirf_serdev_close (struct sirf_data*) ; 
 int sirf_serdev_open (struct sirf_data*) ; 
 int /*<<< orphan*/  sirf_serdev_ops ; 
 int sirf_set_active (struct sirf_data*,int) ; 
 int /*<<< orphan*/  sirf_wakeup_handler ; 

__attribute__((used)) static int sirf_probe(struct serdev_device *serdev)
{
	struct device *dev = &serdev->dev;
	struct gnss_device *gdev;
	struct sirf_data *data;
	int ret;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	gdev = gnss_allocate_device(dev);
	if (!gdev)
		return -ENOMEM;

	gdev->type = GNSS_TYPE_SIRF;
	gdev->ops = &sirf_gnss_ops;
	gnss_set_drvdata(gdev, data);

	data->serdev = serdev;
	data->gdev = gdev;

	mutex_init(&data->gdev_mutex);
	mutex_init(&data->serdev_mutex);
	init_waitqueue_head(&data->power_wait);

	serdev_device_set_drvdata(serdev, data);
	serdev_device_set_client_ops(serdev, &sirf_serdev_ops);

	ret = sirf_parse_dt(serdev);
	if (ret)
		goto err_put_device;

	data->vcc = devm_regulator_get(dev, "vcc");
	if (IS_ERR(data->vcc)) {
		ret = PTR_ERR(data->vcc);
		goto err_put_device;
	}

	data->lna = devm_regulator_get(dev, "lna");
	if (IS_ERR(data->lna)) {
		ret = PTR_ERR(data->lna);
		goto err_put_device;
	}

	data->on_off = devm_gpiod_get_optional(dev, "sirf,onoff",
			GPIOD_OUT_LOW);
	if (IS_ERR(data->on_off))
		goto err_put_device;

	if (data->on_off) {
		data->wakeup = devm_gpiod_get_optional(dev, "sirf,wakeup",
				GPIOD_IN);
		if (IS_ERR(data->wakeup))
			goto err_put_device;

		ret = regulator_enable(data->vcc);
		if (ret)
			goto err_put_device;

		/* Wait for chip to boot into hibernate mode. */
		msleep(SIRF_BOOT_DELAY);
	}

	if (data->wakeup) {
		ret = gpiod_get_value_cansleep(data->wakeup);
		if (ret < 0)
			goto err_disable_vcc;
		data->active = ret;

		ret = gpiod_to_irq(data->wakeup);
		if (ret < 0)
			goto err_disable_vcc;
		data->irq = ret;

		ret = request_threaded_irq(data->irq, NULL, sirf_wakeup_handler,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				"wakeup", data);
		if (ret)
			goto err_disable_vcc;
	}

	if (data->on_off) {
		if (!data->wakeup) {
			data->active = false;

			ret = sirf_serdev_open(data);
			if (ret)
				goto err_disable_vcc;

			msleep(SIRF_REPORT_CYCLE);
			sirf_serdev_close(data);
		}

		/* Force hibernate mode if already active. */
		if (data->active) {
			ret = sirf_set_active(data, false);
			if (ret) {
				dev_err(dev, "failed to set hibernate mode: %d\n",
						ret);
				goto err_free_irq;
			}
		}
	}

	if (IS_ENABLED(CONFIG_PM)) {
		pm_runtime_set_suspended(dev);	/* clear runtime_error flag */
		pm_runtime_enable(dev);
	} else {
		ret = sirf_runtime_resume(dev);
		if (ret < 0)
			goto err_free_irq;
	}

	ret = gnss_register_device(gdev);
	if (ret)
		goto err_disable_rpm;

	return 0;

err_disable_rpm:
	if (IS_ENABLED(CONFIG_PM))
		pm_runtime_disable(dev);
	else
		sirf_runtime_suspend(dev);
err_free_irq:
	if (data->wakeup)
		free_irq(data->irq, data);
err_disable_vcc:
	if (data->on_off)
		regulator_disable(data->vcc);
err_put_device:
	gnss_put_device(data->gdev);

	return ret;
}