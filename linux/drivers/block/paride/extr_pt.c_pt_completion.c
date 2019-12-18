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
struct pt_unit {struct pi_adapter* pi; } ;
struct pi_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAT_BUSY ; 
 int STAT_DRQ ; 
 int STAT_ERR ; 
 int STAT_READY ; 
 int /*<<< orphan*/  pi_disconnect (struct pi_adapter*) ; 
 int /*<<< orphan*/  pi_read_block (struct pi_adapter*,char*,int) ; 
 int /*<<< orphan*/  pi_write_block (struct pi_adapter*,char*,int) ; 
 int pt_wait (struct pt_unit*,int /*<<< orphan*/ ,int,char*,char*) ; 
 int read_reg (struct pi_adapter*,int) ; 

__attribute__((used)) static int pt_completion(struct pt_unit *tape, char *buf, char *fun)
{
	struct pi_adapter *pi = tape->pi;
	int r, s, n, p;

	r = pt_wait(tape, STAT_BUSY, STAT_DRQ | STAT_READY | STAT_ERR,
		    fun, "completion");

	if (read_reg(pi, 7) & STAT_DRQ) {
		n = (((read_reg(pi, 4) + 256 * read_reg(pi, 5)) +
		      3) & 0xfffc);
		p = read_reg(pi, 2) & 3;
		if (p == 0)
			pi_write_block(pi, buf, n);
		if (p == 2)
			pi_read_block(pi, buf, n);
	}

	s = pt_wait(tape, STAT_BUSY, STAT_READY | STAT_ERR, fun, "data done");

	pi_disconnect(pi);

	return (r ? r : s);
}