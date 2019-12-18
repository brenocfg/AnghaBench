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
#define  FSA9480_REG_INT1_MASK 128 

__attribute__((used)) static bool fsa9480_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case FSA9480_REG_INT1_MASK:
		return true;
	default:
		break;
	}
	return false;
}