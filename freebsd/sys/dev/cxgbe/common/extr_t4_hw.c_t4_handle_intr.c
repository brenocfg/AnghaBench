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
typedef  int u32 ;
struct intr_info {scalar_t__ cause_reg; scalar_t__ enable_reg; int fatal; int flags; struct intr_action* actions; } ;
struct intr_action {int mask; int (* action ) (struct adapter*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  arg; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ A_PL_INT_CAUSE ; 
 int NONFATAL_IF_DISABLED ; 
 int stub1 (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int t4_read_reg (struct adapter*,scalar_t__) ; 
 int /*<<< orphan*/  t4_show_intr_info (struct adapter*,struct intr_info const*,int) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,scalar_t__,int) ; 

__attribute__((used)) static bool
t4_handle_intr(struct adapter *adap, const struct intr_info *ii,
    u32 additional_cause, bool verbose)
{
	u32 cause, fatal;
	bool rc;
	const struct intr_action *action;

	/*
	 * Read and display cause.  Note that the top level PL_INT_CAUSE is a
	 * bit special and we need to completely ignore the bits that are not in
	 * PL_INT_ENABLE.
	 */
	cause = t4_read_reg(adap, ii->cause_reg);
	if (ii->cause_reg == A_PL_INT_CAUSE)
		cause &= t4_read_reg(adap, ii->enable_reg);
	if (verbose || cause != 0)
		t4_show_intr_info(adap, ii, cause);
	fatal = cause & ii->fatal;
	if (fatal != 0 && ii->flags & NONFATAL_IF_DISABLED)
		fatal &= t4_read_reg(adap, ii->enable_reg);
	cause |= additional_cause;
	if (cause == 0)
		return (false);

	rc = fatal != 0;
	for (action = ii->actions; action && action->mask != 0; action++) {
		if (!(action->mask & cause))
			continue;
		rc |= (action->action)(adap, action->arg, verbose);
	}

	/* clear */
	t4_write_reg(adap, ii->cause_reg, cause);
	(void)t4_read_reg(adap, ii->cause_reg);

	return (rc);
}