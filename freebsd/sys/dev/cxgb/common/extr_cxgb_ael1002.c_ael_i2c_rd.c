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
struct cphy {int /*<<< orphan*/  addr; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  AEL_I2C_CTRL ; 
 int /*<<< orphan*/  AEL_I2C_DATA ; 
 int /*<<< orphan*/  AEL_I2C_STAT ; 
 int /*<<< orphan*/  CH_WARN (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MDIO_DEV_PMA_PMD ; 
 int mdio_read (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int mdio_write (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int ael_i2c_rd(struct cphy *phy, int dev_addr, int word_addr)
{
	int i, err;
	unsigned int stat, data;

	err = mdio_write(phy, MDIO_DEV_PMA_PMD, AEL_I2C_CTRL,
			 (dev_addr << 8) | (1 << 8) | word_addr);
	if (err)
		return err;

	for (i = 0; i < 200; i++) {
		msleep(1);
		err = mdio_read(phy, MDIO_DEV_PMA_PMD, AEL_I2C_STAT, &stat);
		if (err)
			return err;
		if ((stat & 3) == 1) {
			err = mdio_read(phy, MDIO_DEV_PMA_PMD, AEL_I2C_DATA,
					&data);
			if (err)
				return err;
			return data >> 8;
		}
	}
	CH_WARN(phy->adapter, "PHY %u i2c read of dev.addr %x.%x timed out\n",
		phy->addr, dev_addr, word_addr);
	return -ETIMEDOUT;
}