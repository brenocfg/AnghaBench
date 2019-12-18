#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct atm_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ phy; } ;

/* Variables and functions */
 TYPE_1__* ENI_DEV (struct atm_dev*) ; 
 unsigned char readl (scalar_t__) ; 

__attribute__((used)) static unsigned char eni_phy_get(struct atm_dev *dev,unsigned long addr)
{
	return readl(ENI_DEV(dev)->phy+addr*4);
}