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

/* Variables and functions */
#define  ASPEED_MCR_ADDR_REC 131 
#define  ASPEED_MCR_ADDR_UNREC 130 
#define  ASPEED_MCR_INTR_CTRL 129 
#define  ASPEED_MCR_PROT 128 

__attribute__((used)) static bool regmap_is_volatile(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case ASPEED_MCR_PROT:
	case ASPEED_MCR_INTR_CTRL:
	case ASPEED_MCR_ADDR_UNREC:
	case ASPEED_MCR_ADDR_REC:
		return true;
	default:
		return false;
	}
}