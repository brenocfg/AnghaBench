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
struct notifier_block {int dummy; } ;
struct mce {int dummy; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 int NOTIFY_STOP ; 
 scalar_t__ cec_add_mce (struct mce*) ; 
 int /*<<< orphan*/  mce_need_notify ; 
 int /*<<< orphan*/  mce_notify_irq () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_mce_record (struct mce*) ; 

__attribute__((used)) static int mce_first_notifier(struct notifier_block *nb, unsigned long val,
			      void *data)
{
	struct mce *m = (struct mce *)data;

	if (!m)
		return NOTIFY_DONE;

	if (cec_add_mce(m))
		return NOTIFY_STOP;

	/* Emit the trace record: */
	trace_mce_record(m);

	set_bit(0, &mce_need_notify);

	mce_notify_irq();

	return NOTIFY_DONE;
}