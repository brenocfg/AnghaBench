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
typedef  scalar_t__ u32 ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ KEYLARGO_GPIO_LEVELS0 ; 
 scalar_t__* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 read_gpio(struct device_node *np)
{
	const u32 *reg = of_get_property(np, "reg", NULL);
	u32 offset;

	if (reg == NULL)
		return 0;
	/* That works for all keylargos but shall be fixed properly
	 * some day... The problem is that it seems we can't rely
	 * on the "reg" property of the GPIO nodes, they are either
	 * relative to the base of KeyLargo or to the base of the
	 * GPIO space, and the device-tree doesn't help.
	 */
	offset = *reg;
	if (offset < KEYLARGO_GPIO_LEVELS0)
		offset += KEYLARGO_GPIO_LEVELS0;
	return offset;
}