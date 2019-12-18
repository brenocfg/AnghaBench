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
struct TYPE_4__ {struct rb4xx_cpld_platform_data* platform_data; } ;
struct spi_device {int mode; int bits_per_word; TYPE_1__ dev; } ;
struct rb4xx_cpld_platform_data {int /*<<< orphan*/  gpio_base; } ;
struct rb4xx_cpld {int /*<<< orphan*/  spi; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SPI_MODE_0 ; 
 int SPI_TX_DUAL ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct rb4xx_cpld*) ; 
 int /*<<< orphan*/  kfree (struct rb4xx_cpld*) ; 
 struct rb4xx_cpld* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct rb4xx_cpld* rb4xx_cpld ; 
 int rb4xx_cpld_gpio_init (struct rb4xx_cpld*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_dev_get (struct spi_device*) ; 
 int spi_setup (struct spi_device*) ; 

__attribute__((used)) static int rb4xx_cpld_probe(struct spi_device *spi)
{
	struct rb4xx_cpld *cpld;
	struct rb4xx_cpld_platform_data *pdata;
	int err;

	pdata = spi->dev.platform_data;
	if (!pdata) {
		dev_dbg(&spi->dev, "no platform data\n");
		return -EINVAL;
	}

	cpld = kzalloc(sizeof(*cpld), GFP_KERNEL);
	if (!cpld) {
		dev_err(&spi->dev, "no memory for private data\n");
		return -ENOMEM;
	}

	mutex_init(&cpld->lock);
	cpld->spi = spi_dev_get(spi);
	dev_set_drvdata(&spi->dev, cpld);

	spi->mode = SPI_MODE_0 | SPI_TX_DUAL;
	spi->bits_per_word = 8;
	err = spi_setup(spi);
	if (err) {
		dev_err(&spi->dev, "spi_setup failed, err=%d\n", err);
		goto err_drvdata;
	}

	err = rb4xx_cpld_gpio_init(cpld, pdata->gpio_base);
	if (err)
		goto err_drvdata;

	rb4xx_cpld = cpld;

	return 0;

err_drvdata:
	dev_set_drvdata(&spi->dev, NULL);
	kfree(cpld);

	return err;
}