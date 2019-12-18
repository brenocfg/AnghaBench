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
struct device {int dummy; } ;
struct cs2000_priv {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_CTRL ; 
 int ETIMEDOUT ; 
 int PLL_UNLOCK ; 
 int cs2000_read (struct cs2000_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct device* priv_to_dev (struct cs2000_priv*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int cs2000_wait_pll_lock(struct cs2000_priv *priv)
{
	struct device *dev = priv_to_dev(priv);
	s32 val;
	unsigned int i;

	for (i = 0; i < 256; i++) {
		val = cs2000_read(priv, DEVICE_CTRL);
		if (val < 0)
			return val;
		if (!(val & PLL_UNLOCK))
			return 0;
		udelay(1);
	}

	dev_err(dev, "pll lock failed\n");

	return -ETIMEDOUT;
}