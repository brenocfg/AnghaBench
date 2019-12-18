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
struct pt_unit {int /*<<< orphan*/  name; struct pi_adapter* pi; } ;
struct pi_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVE (struct pt_unit*) ; 
 int STAT_ERR ; 
 int STAT_SEEK ; 
 int /*<<< orphan*/  pi_connect (struct pi_adapter*) ; 
 int /*<<< orphan*/  pi_disconnect (struct pi_adapter*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pt_req_sense (struct pt_unit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_sleep (int) ; 
 int read_reg (struct pi_adapter*,int) ; 
 int /*<<< orphan*/  write_reg (struct pi_adapter*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pt_poll_dsc(struct pt_unit *tape, int pause, int tmo, char *msg)
{
	struct pi_adapter *pi = tape->pi;
	int k, e, s;

	k = 0;
	e = 0;
	s = 0;
	while (k < tmo) {
		pt_sleep(pause);
		k++;
		pi_connect(pi);
		write_reg(pi, 6, DRIVE(tape));
		s = read_reg(pi, 7);
		e = read_reg(pi, 1);
		pi_disconnect(pi);
		if (s & (STAT_ERR | STAT_SEEK))
			break;
	}
	if ((k >= tmo) || (s & STAT_ERR)) {
		if (k >= tmo)
			printk("%s: %s DSC timeout\n", tape->name, msg);
		else
			printk("%s: %s stat=0x%x err=0x%x\n", tape->name, msg, s,
			       e);
		pt_req_sense(tape, 0);
		return 0;
	}
	return 1;
}