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
 int ETIMEDOUT ; 
 int sr16 (struct switch_dev*,int,int) ; 

__attribute__((used)) static int
mvsw61xx_wait_mask_s(struct switch_dev *dev, int addr,
		int reg, u16 mask, u16 val)
{
	int i = 100;
	u16 r;

	do {
		r = sr16(dev, addr, reg) & mask;
		if (r == val)
			return 0;
	} while (--i > 0);

	return -ETIMEDOUT;
}