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
struct intr_info {int flags; int fatal; struct intr_details* details; int /*<<< orphan*/  cause_reg; int /*<<< orphan*/  name; int /*<<< orphan*/  enable_reg; } ;
struct intr_details {int mask; int /*<<< orphan*/  msg; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_ALERT (struct adapter*,char*,int,...) ; 
 int NONFATAL_IF_DISABLED ; 
 char intr_alert_char (int,int,int) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
t4_show_intr_info(struct adapter *adap, const struct intr_info *ii, u32 cause)
{
	u32 enable, fatal, leftover;
	const struct intr_details *details;
	char alert;

	enable = t4_read_reg(adap, ii->enable_reg);
	if (ii->flags & NONFATAL_IF_DISABLED)
		fatal = ii->fatal & t4_read_reg(adap, ii->enable_reg);
	else
		fatal = ii->fatal;
	alert = intr_alert_char(cause, enable, fatal);
	CH_ALERT(adap, "%c %s 0x%x = 0x%08x, E 0x%08x, F 0x%08x\n",
	    alert, ii->name, ii->cause_reg, cause, enable, fatal);

	leftover = cause;
	for (details = ii->details; details && details->mask != 0; details++) {
		u32 msgbits = details->mask & cause;
		if (msgbits == 0)
			continue;
		alert = intr_alert_char(msgbits, enable, ii->fatal);
		CH_ALERT(adap, "  %c [0x%08x] %s\n", alert, msgbits,
		    details->msg);
		leftover &= ~msgbits;
	}
	if (leftover != 0 && leftover != cause)
		CH_ALERT(adap, "  ? [0x%08x]\n", leftover);
}