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
struct pg {int status; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PG_SPIN ; 
 int /*<<< orphan*/  PG_SPIN_DEL ; 
 int STAT_ERR ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  pg_sleep (int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,char*,int,int,int,char*) ; 
 int read_reg (struct pg*,int) ; 
 int status_reg (struct pg*) ; 
 int time_after_eq (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int verbose ; 

__attribute__((used)) static int pg_wait(struct pg *dev, int go, int stop, unsigned long tmo, char *msg)
{
	int j, r, e, s, p, to;

	dev->status = 0;

	j = 0;
	while ((((r = status_reg(dev)) & go) || (stop && (!(r & stop))))
	       && time_before(jiffies, tmo)) {
		if (j++ < PG_SPIN)
			udelay(PG_SPIN_DEL);
		else
			pg_sleep(1);
	}

	to = time_after_eq(jiffies, tmo);

	if ((r & (STAT_ERR & stop)) || to) {
		s = read_reg(dev, 7);
		e = read_reg(dev, 1);
		p = read_reg(dev, 2);
		if (verbose > 1)
			printk("%s: %s: stat=0x%x err=0x%x phase=%d%s\n",
			       dev->name, msg, s, e, p, to ? " timeout" : "");
		if (to)
			e |= 0x100;
		dev->status = (e >> 4) & 0xff;
		return -1;
	}
	return 0;
}