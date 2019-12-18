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
typedef  int u8 ;
struct ts73xx_fpga_priv {scalar_t__ io_base; } ;
struct fpga_manager {struct ts73xx_fpga_priv* priv; } ;

/* Variables and functions */
 scalar_t__ TS73XX_FPGA_CONFIG_REG ; 
 scalar_t__ TS73XX_FPGA_DATA_REG ; 
 int TS73XX_FPGA_WRITE_DONE ; 
 int /*<<< orphan*/  TS73XX_FPGA_WRITE_DONE_TIMEOUT ; 
 int readb_poll_timeout (scalar_t__,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (char const,scalar_t__) ; 

__attribute__((used)) static int ts73xx_fpga_write(struct fpga_manager *mgr, const char *buf,
			     size_t count)
{
	struct ts73xx_fpga_priv *priv = mgr->priv;
	size_t i = 0;
	int ret;
	u8 reg;

	while (count--) {
		ret = readb_poll_timeout(priv->io_base + TS73XX_FPGA_CONFIG_REG,
					 reg, !(reg & TS73XX_FPGA_WRITE_DONE),
					 1, TS73XX_FPGA_WRITE_DONE_TIMEOUT);
		if (ret < 0)
			return ret;

		writeb(buf[i], priv->io_base + TS73XX_FPGA_DATA_REG);
		i++;
	}

	return 0;
}