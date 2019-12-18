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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_TP_PACE_TABLE ; 
 unsigned int NTX_SCHED ; 
 unsigned int dack_ticks_to_usec (struct adapter*,unsigned int) ; 
 unsigned int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

void t4_read_pace_tbl(struct adapter *adap, unsigned int pace_vals[NTX_SCHED])
{
	unsigned int i, v;

	for (i = 0; i < NTX_SCHED; i++) {
		t4_write_reg(adap, A_TP_PACE_TABLE, 0xffff0000 + i);
		v = t4_read_reg(adap, A_TP_PACE_TABLE);
		pace_vals[i] = dack_ticks_to_usec(adap, v);
	}
}