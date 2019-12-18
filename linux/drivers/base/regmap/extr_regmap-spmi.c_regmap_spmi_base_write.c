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

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int regmap_spmi_base_gather_write (void*,void const*,int,void const*,size_t) ; 

__attribute__((used)) static int regmap_spmi_base_write(void *context, const void *data,
				  size_t count)
{
	BUG_ON(count < 1);
	return regmap_spmi_base_gather_write(context, data, 1, data + 1,
					     count - 1);
}