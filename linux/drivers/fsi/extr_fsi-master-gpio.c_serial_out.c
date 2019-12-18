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
typedef  int uint8_t ;
typedef  int uint64_t ;
struct fsi_master_gpio {int /*<<< orphan*/  dev; } ;
struct fsi_gpio_msg {int msg; int bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  clock_toggle (struct fsi_master_gpio*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sda_out (struct fsi_master_gpio*,int) ; 
 int /*<<< orphan*/  set_sda_output (struct fsi_master_gpio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_fsi_master_gpio_out (struct fsi_master_gpio*,int,int) ; 

__attribute__((used)) static void serial_out(struct fsi_master_gpio *master,
			const struct fsi_gpio_msg *cmd)
{
	uint8_t bit;
	uint64_t msg = ~cmd->msg;	/* Data is active low */
	uint64_t sda_mask = 0x1ULL << (cmd->bits - 1);
	uint64_t last_bit = ~0;
	int next_bit;

	trace_fsi_master_gpio_out(master, cmd->bits, cmd->msg);

	if (!cmd->bits) {
		dev_warn(master->dev, "trying to output 0 bits\n");
		return;
	}
	set_sda_output(master, 0);

	/* Send the start bit */
	sda_out(master, 0);
	clock_toggle(master, 1);

	/* Send the message */
	for (bit = 0; bit < cmd->bits; bit++) {
		next_bit = (msg & sda_mask) >> (cmd->bits - 1);
		if (last_bit ^ next_bit) {
			sda_out(master, next_bit);
			last_bit = next_bit;
		}
		clock_toggle(master, 1);
		msg <<= 1;
	}
}