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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int spmi_register_read (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int regmap_spmi_base_read(void *context,
				 const void *reg, size_t reg_size,
				 void *val, size_t val_size)
{
	u8 addr = *(u8 *)reg;
	int err = 0;

	BUG_ON(reg_size != 1);

	while (val_size-- && !err)
		err = spmi_register_read(context, addr++, val++);

	return err;
}