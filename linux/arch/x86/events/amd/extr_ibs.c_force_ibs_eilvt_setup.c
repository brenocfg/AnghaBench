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

/* Variables and functions */
 int APIC_EILVT_NR_MAX ; 
 scalar_t__ get_eilvt (int) ; 
 int /*<<< orphan*/  ibs_eilvt_valid () ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  put_eilvt (int) ; 
 int setup_ibs_ctl (int) ; 

__attribute__((used)) static void force_ibs_eilvt_setup(void)
{
	int offset;
	int ret;

	preempt_disable();
	/* find the next free available EILVT entry, skip offset 0 */
	for (offset = 1; offset < APIC_EILVT_NR_MAX; offset++) {
		if (get_eilvt(offset))
			break;
	}
	preempt_enable();

	if (offset == APIC_EILVT_NR_MAX) {
		pr_debug("No EILVT entry available\n");
		return;
	}

	ret = setup_ibs_ctl(offset);
	if (ret)
		goto out;

	if (!ibs_eilvt_valid())
		goto out;

	pr_info("LVT offset %d assigned\n", offset);

	return;
out:
	preempt_disable();
	put_eilvt(offset);
	preempt_enable();
	return;
}