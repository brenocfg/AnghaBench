#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct mce {int status; int bank; } ;
struct TYPE_4__ {int /*<<< orphan*/  tolerant; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* status ) (int) ;} ;

/* Variables and functions */
 scalar_t__ MCE_PANIC_SEVERITY ; 
 int MCI_STATUS_VAL ; 
 int /*<<< orphan*/  __set_bit (int,unsigned long*) ; 
 TYPE_2__ mca_cfg ; 
 int /*<<< orphan*/  mce_num_banks ; 
 int mce_rdmsrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mce_read_aux (struct mce*,int) ; 
 scalar_t__ mce_severity (struct mce*,int /*<<< orphan*/ ,char**,int) ; 
 TYPE_1__ msr_ops ; 
 int /*<<< orphan*/  quirk_no_way_out (int,struct mce*,struct pt_regs*) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int this_cpu_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mce_no_way_out(struct mce *m, char **msg, unsigned long *validp,
			  struct pt_regs *regs)
{
	char *tmp;
	int i;

	for (i = 0; i < this_cpu_read(mce_num_banks); i++) {
		m->status = mce_rdmsrl(msr_ops.status(i));
		if (!(m->status & MCI_STATUS_VAL))
			continue;

		__set_bit(i, validp);
		if (quirk_no_way_out)
			quirk_no_way_out(i, m, regs);

		if (mce_severity(m, mca_cfg.tolerant, &tmp, true) >= MCE_PANIC_SEVERITY) {
			m->bank = i;
			mce_read_aux(m, i);
			*msg = tmp;
			return 1;
		}
	}
	return 0;
}