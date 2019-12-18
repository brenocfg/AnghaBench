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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct zpci_fib {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZPCI_INSN_BUSY_DELAY ; 
 int __mpcifc (int /*<<< orphan*/ ,struct zpci_fib*,int*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpci_err_insn (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u8 zpci_mod_fc(u64 req, struct zpci_fib *fib, u8 *status)
{
	u8 cc;

	do {
		cc = __mpcifc(req, fib, status);
		if (cc == 2)
			msleep(ZPCI_INSN_BUSY_DELAY);
	} while (cc == 2);

	if (cc)
		zpci_err_insn(cc, *status, req, 0);

	return cc;
}