#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct adm6996_gpio_platform_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct adm6996_priv {int /*<<< orphan*/  eesk; int /*<<< orphan*/  eedi; int /*<<< orphan*/  eecs; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  model; int /*<<< orphan*/  mib_lock; int /*<<< orphan*/  reg_mutex; } ;
struct adm6996_gpio_platform_data {int /*<<< orphan*/  model; int /*<<< orphan*/  eesk; int /*<<< orphan*/  eedi; int /*<<< orphan*/  eecs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  adm6996_read_gpio_reg ; 
 int adm6996_switch_init (struct adm6996_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adm6996_write_gpio_reg ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int devm_gpio_request (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 struct adm6996_priv* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct adm6996_priv*) ; 

__attribute__((used)) static int adm6996_gpio_probe(struct platform_device *pdev)
{
	struct adm6996_gpio_platform_data *pdata = pdev->dev.platform_data;
	struct adm6996_priv *priv;
	int ret;

	if (!pdata)
		return -EINVAL;

	priv = devm_kzalloc(&pdev->dev, sizeof(struct adm6996_priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	mutex_init(&priv->reg_mutex);
	mutex_init(&priv->mib_lock);

	priv->eecs = pdata->eecs;
	priv->eedi = pdata->eedi;
	priv->eesk = pdata->eesk;

	priv->model = pdata->model;
	priv->read = adm6996_read_gpio_reg;
	priv->write = adm6996_write_gpio_reg;

	ret = devm_gpio_request(&pdev->dev, priv->eecs, "adm_eecs");
	if (ret)
		return ret;
	ret = devm_gpio_request(&pdev->dev, priv->eedi, "adm_eedi");
	if (ret)
		return ret;
	ret = devm_gpio_request(&pdev->dev, priv->eesk, "adm_eesk");
	if (ret)
		return ret;

	ret = adm6996_switch_init(priv, dev_name(&pdev->dev), NULL);
	if (ret < 0)
		return ret;

	platform_set_drvdata(pdev, priv);

	return 0;
}