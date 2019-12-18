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
typedef  int /*<<< orphan*/  u16 ;
struct ep93xx_pata_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ep93xx_pata_read (struct ep93xx_pata_data*,unsigned long,int) ; 

__attribute__((used)) static u16 ep93xx_pata_read_reg(struct ep93xx_pata_data *drv_data,
				unsigned long addr)
{
	return ep93xx_pata_read(drv_data, addr, true);
}