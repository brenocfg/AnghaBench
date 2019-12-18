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
struct serdev_device {int /*<<< orphan*/  dev; } ;
struct mtk_data {struct gnss_serial* vbackup; struct gnss_serial* vcc; } ;
struct gnss_serial {TYPE_1__* gdev; int /*<<< orphan*/ * ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GNSS_TYPE_MTK ; 
 scalar_t__ IS_ERR (struct gnss_serial*) ; 
 int PTR_ERR (struct gnss_serial*) ; 
 struct gnss_serial* devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 struct gnss_serial* devm_regulator_get_optional (int /*<<< orphan*/ *,char*) ; 
 struct gnss_serial* gnss_serial_allocate (struct serdev_device*,int) ; 
 int /*<<< orphan*/  gnss_serial_free (struct gnss_serial*) ; 
 struct mtk_data* gnss_serial_get_drvdata (struct gnss_serial*) ; 
 int gnss_serial_register (struct gnss_serial*) ; 
 int /*<<< orphan*/  mtk_gserial_ops ; 
 int /*<<< orphan*/  regulator_disable (struct gnss_serial*) ; 
 int regulator_enable (struct gnss_serial*) ; 

__attribute__((used)) static int mtk_probe(struct serdev_device *serdev)
{
	struct gnss_serial *gserial;
	struct mtk_data *data;
	int ret;

	gserial = gnss_serial_allocate(serdev, sizeof(*data));
	if (IS_ERR(gserial)) {
		ret = PTR_ERR(gserial);
		return ret;
	}

	gserial->ops = &mtk_gserial_ops;

	gserial->gdev->type = GNSS_TYPE_MTK;

	data = gnss_serial_get_drvdata(gserial);

	data->vcc = devm_regulator_get(&serdev->dev, "vcc");
	if (IS_ERR(data->vcc)) {
		ret = PTR_ERR(data->vcc);
		goto err_free_gserial;
	}

	data->vbackup = devm_regulator_get_optional(&serdev->dev, "vbackup");
	if (IS_ERR(data->vbackup)) {
		ret = PTR_ERR(data->vbackup);
		if (ret == -ENODEV)
			data->vbackup = NULL;
		else
			goto err_free_gserial;
	}

	if (data->vbackup) {
		ret = regulator_enable(data->vbackup);
		if (ret)
			goto err_free_gserial;
	}

	ret = gnss_serial_register(gserial);
	if (ret)
		goto err_disable_vbackup;

	return 0;

err_disable_vbackup:
	if (data->vbackup)
		regulator_disable(data->vbackup);
err_free_gserial:
	gnss_serial_free(gserial);

	return ret;
}