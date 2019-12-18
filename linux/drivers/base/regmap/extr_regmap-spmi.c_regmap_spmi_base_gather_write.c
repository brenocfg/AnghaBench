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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int spmi_register_write (void*,scalar_t__,scalar_t__ const) ; 
 int spmi_register_zero_write (void*,scalar_t__ const) ; 

__attribute__((used)) static int regmap_spmi_base_gather_write(void *context,
					 const void *reg, size_t reg_size,
					 const void *val, size_t val_size)
{
	const u8 *data = val;
	u8 addr = *(u8 *)reg;
	int err = 0;

	BUG_ON(reg_size != 1);

	/*
	 * SPMI defines a more bandwidth-efficient 'Register 0 Write' sequence,
	 * use it when possible.
	 */
	if (addr == 0 && val_size) {
		err = spmi_register_zero_write(context, *data);
		if (err)
			goto err_out;

		data++;
		addr++;
		val_size--;
	}

	while (val_size) {
		err = spmi_register_write(context, addr, *data);
		if (err)
			goto err_out;

		data++;
		addr++;
		val_size--;
	}

err_out:
	return err;
}