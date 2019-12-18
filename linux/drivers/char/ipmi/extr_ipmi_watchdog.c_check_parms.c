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
 int /*<<< orphan*/  NMI_UNKNOWN ; 
 scalar_t__ WDOG_PREOP_GIVE_DATA ; 
 scalar_t__ WDOG_PRETIMEOUT_NMI ; 
 int /*<<< orphan*/  ipmi_nmi ; 
 int nmi_handler_registered ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ preaction_val ; 
 int /*<<< orphan*/  preop_op (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ preop_val ; 
 int register_nmi_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unregister_nmi_handler (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void check_parms(void)
{
#ifdef HAVE_DIE_NMI
	int do_nmi = 0;
	int rv;

	if (preaction_val == WDOG_PRETIMEOUT_NMI) {
		do_nmi = 1;
		if (preop_val == WDOG_PREOP_GIVE_DATA) {
			pr_warn("Pretimeout op is to give data but NMI pretimeout is enabled, setting pretimeout op to none\n");
			preop_op("preop_none", NULL);
			do_nmi = 0;
		}
	}
	if (do_nmi && !nmi_handler_registered) {
		rv = register_nmi_handler(NMI_UNKNOWN, ipmi_nmi, 0,
						"ipmi");
		if (rv) {
			pr_warn("Can't register nmi handler\n");
			return;
		} else
			nmi_handler_registered = 1;
	} else if (!do_nmi && nmi_handler_registered) {
		unregister_nmi_handler(NMI_UNKNOWN, "ipmi");
		nmi_handler_registered = 0;
	}
#endif
}