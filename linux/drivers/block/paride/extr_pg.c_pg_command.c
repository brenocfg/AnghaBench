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
struct pg {int /*<<< orphan*/  pi; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int DRIVE (struct pg*) ; 
 int STAT_BUSY ; 
 int STAT_DRQ ; 
 scalar_t__ pg_wait (struct pg*,int,int,unsigned long,char*) ; 
 int /*<<< orphan*/  pi_connect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pi_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pi_write_block (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int read_reg (struct pg*,int) ; 
 int verbose ; 
 int /*<<< orphan*/  write_reg (struct pg*,int,int) ; 

__attribute__((used)) static int pg_command(struct pg *dev, char *cmd, int dlen, unsigned long tmo)
{
	int k;

	pi_connect(dev->pi);

	write_reg(dev, 6, DRIVE(dev));

	if (pg_wait(dev, STAT_BUSY | STAT_DRQ, 0, tmo, "before command"))
		goto fail;

	write_reg(dev, 4, dlen % 256);
	write_reg(dev, 5, dlen / 256);
	write_reg(dev, 7, 0xa0);	/* ATAPI packet command */

	if (pg_wait(dev, STAT_BUSY, STAT_DRQ, tmo, "command DRQ"))
		goto fail;

	if (read_reg(dev, 2) != 1) {
		printk("%s: command phase error\n", dev->name);
		goto fail;
	}

	pi_write_block(dev->pi, cmd, 12);

	if (verbose > 1) {
		printk("%s: Command sent, dlen=%d packet= ", dev->name, dlen);
		for (k = 0; k < 12; k++)
			printk("%02x ", cmd[k] & 0xff);
		printk("\n");
	}
	return 0;
fail:
	pi_disconnect(dev->pi);
	return -1;
}