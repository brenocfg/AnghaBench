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
typedef  scalar_t__ uint8_t ;
struct fsi_master_gpio {int dummy; } ;
struct fsi_gpio_msg {int msg; int /*<<< orphan*/  bits; } ;

/* Variables and functions */
 scalar_t__ sda_clock_in (struct fsi_master_gpio*) ; 
 int /*<<< orphan*/  set_sda_input (struct fsi_master_gpio*) ; 
 int /*<<< orphan*/  trace_fsi_master_gpio_in (struct fsi_master_gpio*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void serial_in(struct fsi_master_gpio *master, struct fsi_gpio_msg *msg,
			uint8_t num_bits)
{
	uint8_t bit, in_bit;

	set_sda_input(master);

	for (bit = 0; bit < num_bits; bit++) {
		in_bit = sda_clock_in(master);
		msg->msg <<= 1;
		msg->msg |= ~in_bit & 0x1;	/* Data is active low */
	}
	msg->bits += num_bits;

	trace_fsi_master_gpio_in(master, num_bits, msg->msg);
}