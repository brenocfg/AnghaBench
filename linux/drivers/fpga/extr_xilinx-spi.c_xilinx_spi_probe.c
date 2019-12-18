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
struct xilinx_spi_conf {void* done; void* prog_b; struct spi_device* spi; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct fpga_manager {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct fpga_manager* devm_fpga_mgr_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,struct xilinx_spi_conf*) ; 
 void* devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct xilinx_spi_conf* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int fpga_mgr_register (struct fpga_manager*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct fpga_manager*) ; 
 int /*<<< orphan*/  xilinx_spi_ops ; 

__attribute__((used)) static int xilinx_spi_probe(struct spi_device *spi)
{
	struct xilinx_spi_conf *conf;
	struct fpga_manager *mgr;

	conf = devm_kzalloc(&spi->dev, sizeof(*conf), GFP_KERNEL);
	if (!conf)
		return -ENOMEM;

	conf->spi = spi;

	/* PROGRAM_B is active low */
	conf->prog_b = devm_gpiod_get(&spi->dev, "prog_b", GPIOD_OUT_LOW);
	if (IS_ERR(conf->prog_b)) {
		dev_err(&spi->dev, "Failed to get PROGRAM_B gpio: %ld\n",
			PTR_ERR(conf->prog_b));
		return PTR_ERR(conf->prog_b);
	}

	conf->done = devm_gpiod_get(&spi->dev, "done", GPIOD_IN);
	if (IS_ERR(conf->done)) {
		dev_err(&spi->dev, "Failed to get DONE gpio: %ld\n",
			PTR_ERR(conf->done));
		return PTR_ERR(conf->done);
	}

	mgr = devm_fpga_mgr_create(&spi->dev,
				   "Xilinx Slave Serial FPGA Manager",
				   &xilinx_spi_ops, conf);
	if (!mgr)
		return -ENOMEM;

	spi_set_drvdata(spi, mgr);

	return fpga_mgr_register(mgr);
}