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
struct mii_bus {int (* read ) (struct mii_bus*,int,int) ;} ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int stub1 (struct mii_bus*,int,int) ; 

__attribute__((used)) static int
mvsw61xx_wait_mask_raw(struct mii_bus *bus, int addr,
		int reg, u16 mask, u16 val)
{
	int i = 100;
	u16 r;

	do {
		r = bus->read(bus, addr, reg);
		if ((r & mask) == val)
			return 0;
	} while (--i > 0);

	return -ETIMEDOUT;
}