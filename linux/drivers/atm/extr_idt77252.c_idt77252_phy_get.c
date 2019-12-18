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
struct atm_dev {int /*<<< orphan*/  dev_data; } ;

/* Variables and functions */
 unsigned char read_utility (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned char
idt77252_phy_get(struct atm_dev *dev, unsigned long addr)
{
	return read_utility(dev->dev_data, 0x100 + (addr & 0x1ff));
}