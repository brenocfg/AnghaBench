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
struct tc {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVPCONTROL_VPC ; 
 int /*<<< orphan*/  TCHALT_H ; 
 int TCSTATUS_A ; 
 int TCSTATUS_DA ; 
 int TCSTATUS_IXMT ; 
 int /*<<< orphan*/  clear_c0_mvpcontrol (int /*<<< orphan*/ ) ; 
 unsigned int dmt () ; 
 unsigned int dvpe () ; 
 int /*<<< orphan*/  emt (unsigned int) ; 
 int /*<<< orphan*/  evpe (unsigned int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mips_ihb () ; 
 int read_tc_c0_tcstatus () ; 
 int /*<<< orphan*/  set_c0_mvpcontrol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  settc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_tc_c0_tchalt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_tc_c0_tcstatus (int) ; 

void cleanup_tc(struct tc *tc)
{
	unsigned long flags;
	unsigned int mtflags, vpflags;
	int tmp;

	local_irq_save(flags);
	mtflags = dmt();
	vpflags = dvpe();
	/* Put MVPE's into 'configuration state' */
	set_c0_mvpcontrol(MVPCONTROL_VPC);

	settc(tc->index);
	tmp = read_tc_c0_tcstatus();

	/* mark not allocated and not dynamically allocatable */
	tmp &= ~(TCSTATUS_A | TCSTATUS_DA);
	tmp |= TCSTATUS_IXMT;	/* interrupt exempt */
	write_tc_c0_tcstatus(tmp);

	write_tc_c0_tchalt(TCHALT_H);
	mips_ihb();

	clear_c0_mvpcontrol(MVPCONTROL_VPC);
	evpe(vpflags);
	emt(mtflags);
	local_irq_restore(flags);
}