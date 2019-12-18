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
struct spi_master {int num_chipselect; int /*<<< orphan*/  transfer; int /*<<< orphan*/  setup; int /*<<< orphan*/  mode_bits; scalar_t__ bus_num; } ;
struct resource {scalar_t__ start; scalar_t__ end; } ;
struct rb4xx_spi {int cs_wait; int /*<<< orphan*/  ahb_clk; int /*<<< orphan*/  base; int /*<<< orphan*/  queue; int /*<<< orphan*/  lock; void* spi_ctrl_fread; void* spi_ctrl_flash; struct spi_master* master; int /*<<< orphan*/  ahb_freq; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_CPLD_HZ ; 
 int /*<<< orphan*/  SPI_FLASH_HZ ; 
 int /*<<< orphan*/  SPI_TX_DUAL ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* get_spi_ctrl (struct rb4xx_spi*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ioremap (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rb4xx_spi*) ; 
 int /*<<< orphan*/  rb4xx_spi_setup ; 
 int /*<<< orphan*/  rb4xx_spi_transfer ; 
 struct spi_master* spi_alloc_master (int /*<<< orphan*/ *,int) ; 
 struct rb4xx_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 
 int spi_register_master (struct spi_master*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rb4xx_spi_probe(struct platform_device *pdev)
{
	struct spi_master *master;
	struct rb4xx_spi *rbspi;
	struct resource *r;
	int err = 0;

	master = spi_alloc_master(&pdev->dev, sizeof(*rbspi));
	if (master == NULL) {
		dev_err(&pdev->dev, "no memory for spi_master\n");
		err = -ENOMEM;
		goto err_out;
	}

	master->bus_num = 0;
	master->num_chipselect = 3;
	master->mode_bits = SPI_TX_DUAL;
	master->setup = rb4xx_spi_setup;
	master->transfer = rb4xx_spi_transfer;

	rbspi = spi_master_get_devdata(master);

	rbspi->ahb_clk = clk_get(&pdev->dev, "ahb");
	if (IS_ERR(rbspi->ahb_clk)) {
		err = PTR_ERR(rbspi->ahb_clk);
		goto err_put_master;
	}

	err = clk_prepare_enable(rbspi->ahb_clk);
	if (err)
		goto err_clk_put;

	rbspi->ahb_freq = clk_get_rate(rbspi->ahb_clk);
	if (!rbspi->ahb_freq) {
		err = -EINVAL;
		goto err_clk_disable;
	}

	platform_set_drvdata(pdev, rbspi);

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (r == NULL) {
		err = -ENOENT;
		goto err_clk_disable;
	}

	rbspi->base = ioremap(r->start, r->end - r->start + 1);
	if (!rbspi->base) {
		err = -ENXIO;
		goto err_clk_disable;
	}

	rbspi->master = master;
	rbspi->spi_ctrl_flash = get_spi_ctrl(rbspi, SPI_FLASH_HZ, "FLASH");
	rbspi->spi_ctrl_fread = get_spi_ctrl(rbspi, SPI_CPLD_HZ, "CPLD");
	rbspi->cs_wait = -1;

	spin_lock_init(&rbspi->lock);
	INIT_LIST_HEAD(&rbspi->queue);

	err = spi_register_master(master);
	if (err) {
		dev_err(&pdev->dev, "failed to register SPI master\n");
		goto err_iounmap;
	}

	return 0;

err_iounmap:
	iounmap(rbspi->base);
err_clk_disable:
	clk_disable_unprepare(rbspi->ahb_clk);
err_clk_put:
	clk_put(rbspi->ahb_clk);
err_put_master:
	platform_set_drvdata(pdev, NULL);
	spi_master_put(master);
err_out:
	return err;
}