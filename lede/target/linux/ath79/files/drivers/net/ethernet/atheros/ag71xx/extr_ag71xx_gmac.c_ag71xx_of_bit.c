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
 scalar_t__ of_property_read_u32 (struct device_node*,char const*,scalar_t__*) ; 

__attribute__((used)) static void ag71xx_of_bit(struct device_node *np, const char *prop,
			  u32 *reg, u32 mask)
{
	u32 val;

	if (of_property_read_u32(np, prop, &val))
		return;

	if (val)
		*reg |= mask;
	else
		*reg &= ~mask;
}