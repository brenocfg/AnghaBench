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
typedef  int u16 ;
struct switch_dev {int dummy; } ;

/* Variables and functions */
 int MII_MV_PAGE ; 
 int /*<<< orphan*/  mvsw61xx_mdio_write (struct switch_dev*,int,int,int) ; 

__attribute__((used)) static void
mvsw61xx_mdio_page_write(struct switch_dev *dev, int port, int page, int reg,
			 u16 val)
{
	mvsw61xx_mdio_write(dev, port, MII_MV_PAGE, page);
	mvsw61xx_mdio_write(dev, port, reg, val);
	mvsw61xx_mdio_write(dev, port, MII_MV_PAGE, 0);
}