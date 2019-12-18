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
struct fpga_manager {int /*<<< orphan*/  dev; struct altera_ps_conf* priv; } ;
struct fpga_image_info {int dummy; } ;
struct altera_ps_conf {int /*<<< orphan*/  spi; scalar_t__ confd; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  gpiod_get_raw_value_cansleep (scalar_t__) ; 
 scalar_t__ gpiod_get_value_cansleep (int /*<<< orphan*/ ) ; 
 int spi_write (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int altera_ps_write_complete(struct fpga_manager *mgr,
				    struct fpga_image_info *info)
{
	struct altera_ps_conf *conf = mgr->priv;
	static const char dummy[] = {0};
	int ret;

	if (gpiod_get_value_cansleep(conf->status)) {
		dev_err(&mgr->dev, "Error during configuration.\n");
		return -EIO;
	}

	if (conf->confd) {
		if (!gpiod_get_raw_value_cansleep(conf->confd)) {
			dev_err(&mgr->dev, "CONF_DONE is inactive!\n");
			return -EIO;
		}
	}

	/*
	 * After CONF_DONE goes high, send two additional falling edges on DCLK
	 * to begin initialization and enter user mode
	 */
	ret = spi_write(conf->spi, dummy, 1);
	if (ret) {
		dev_err(&mgr->dev, "spi error during end sequence: %d\n", ret);
		return ret;
	}

	return 0;
}