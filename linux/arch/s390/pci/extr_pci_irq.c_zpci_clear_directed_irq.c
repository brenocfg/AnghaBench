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
struct zpci_fib {int fmt; int /*<<< orphan*/  member_0; } ;
struct zpci_dev {int /*<<< orphan*/  fh; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ZPCI_CREATE_REQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZPCI_MOD_FC_DEREG_INT_D ; 
 int zpci_mod_fc (int /*<<< orphan*/ ,struct zpci_fib*,int*) ; 

__attribute__((used)) static int zpci_clear_directed_irq(struct zpci_dev *zdev)
{
	u64 req = ZPCI_CREATE_REQ(zdev->fh, 0, ZPCI_MOD_FC_DEREG_INT_D);
	struct zpci_fib fib = {0};
	u8 cc, status;

	fib.fmt = 1;
	cc = zpci_mod_fc(req, &fib, &status);
	if (cc == 3 || (cc == 1 && status == 24))
		/* Function already gone or IRQs already deregistered. */
		cc = 0;

	return cc ? -EIO : 0;
}