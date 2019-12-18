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
typedef  int u32 ;
struct bcma_drv_cc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CC_GPIOIN ; 
 int bcma_cc_read32 (struct bcma_drv_cc*,int /*<<< orphan*/ ) ; 

u32 bcma_chipco_gpio_in(struct bcma_drv_cc *cc, u32 mask)
{
	return bcma_cc_read32(cc, BCMA_CC_GPIOIN) & mask;
}