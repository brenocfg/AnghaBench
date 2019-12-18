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
struct xilinx_spi_conf {int /*<<< orphan*/  done; } ;
struct fpga_manager {int /*<<< orphan*/  dev; struct xilinx_spi_conf* priv; } ;
struct fpga_image_info {int /*<<< orphan*/  config_complete_timeout_us; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ gpiod_get_value (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 unsigned long usecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int xilinx_spi_apply_cclk_cycles (struct xilinx_spi_conf*) ; 

__attribute__((used)) static int xilinx_spi_write_complete(struct fpga_manager *mgr,
				     struct fpga_image_info *info)
{
	struct xilinx_spi_conf *conf = mgr->priv;
	unsigned long timeout;
	int ret;

	if (gpiod_get_value(conf->done))
		return xilinx_spi_apply_cclk_cycles(conf);

	timeout = jiffies + usecs_to_jiffies(info->config_complete_timeout_us);

	while (time_before(jiffies, timeout)) {

		ret = xilinx_spi_apply_cclk_cycles(conf);
		if (ret)
			return ret;

		if (gpiod_get_value(conf->done))
			return xilinx_spi_apply_cclk_cycles(conf);
	}

	dev_err(&mgr->dev, "Timeout after config data transfer.\n");
	return -ETIMEDOUT;
}