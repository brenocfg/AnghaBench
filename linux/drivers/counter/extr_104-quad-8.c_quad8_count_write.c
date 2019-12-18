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
struct quad8_iio {int base; unsigned long* preset; } ;
struct counter_device {struct quad8_iio* priv; } ;
struct counter_count_write_value {int dummy; } ;
struct counter_count {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_COUNT_POSITION ; 
 int EINVAL ; 
 unsigned long QUAD8_CTR_RLD ; 
 unsigned long QUAD8_RLD_PRESET_CNTR ; 
 unsigned long QUAD8_RLD_RESET_BP ; 
 unsigned long QUAD8_RLD_RESET_E ; 
 unsigned long QUAD8_RLD_RESET_FLAGS ; 
 int counter_count_write_value_get (unsigned long*,int /*<<< orphan*/ ,struct counter_count_write_value*) ; 
 int /*<<< orphan*/  outb (unsigned long,int const) ; 

__attribute__((used)) static int quad8_count_write(struct counter_device *counter,
	struct counter_count *count, struct counter_count_write_value *val)
{
	const struct quad8_iio *const priv = counter->priv;
	const int base_offset = priv->base + 2 * count->id;
	int err;
	unsigned long position;
	int i;

	err = counter_count_write_value_get(&position, COUNTER_COUNT_POSITION,
					    val);
	if (err)
		return err;

	/* Only 24-bit values are supported */
	if (position > 0xFFFFFF)
		return -EINVAL;

	/* Reset Byte Pointer */
	outb(QUAD8_CTR_RLD | QUAD8_RLD_RESET_BP, base_offset + 1);

	/* Counter can only be set via Preset Register */
	for (i = 0; i < 3; i++)
		outb(position >> (8 * i), base_offset);

	/* Transfer Preset Register to Counter */
	outb(QUAD8_CTR_RLD | QUAD8_RLD_PRESET_CNTR, base_offset + 1);

	/* Reset Byte Pointer */
	outb(QUAD8_CTR_RLD | QUAD8_RLD_RESET_BP, base_offset + 1);

	/* Set Preset Register back to original value */
	position = priv->preset[count->id];
	for (i = 0; i < 3; i++)
		outb(position >> (8 * i), base_offset);

	/* Reset Borrow, Carry, Compare, and Sign flags */
	outb(QUAD8_CTR_RLD | QUAD8_RLD_RESET_FLAGS, base_offset + 1);
	/* Reset Error flag */
	outb(QUAD8_CTR_RLD | QUAD8_RLD_RESET_E, base_offset + 1);

	return 0;
}