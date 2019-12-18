#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  dibvo; int /*<<< orphan*/  noi; } ;
struct zpci_fib {int fmt; TYPE_1__ fmt1; int /*<<< orphan*/  member_0; } ;
struct zpci_dev {int /*<<< orphan*/  msi_first_bit; int /*<<< orphan*/  msi_nr_irqs; int /*<<< orphan*/  fh; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ZPCI_CREATE_REQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZPCI_MOD_FC_REG_INT_D ; 
 scalar_t__ zpci_mod_fc (int /*<<< orphan*/ ,struct zpci_fib*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zpci_set_directed_irq(struct zpci_dev *zdev)
{
	u64 req = ZPCI_CREATE_REQ(zdev->fh, 0, ZPCI_MOD_FC_REG_INT_D);
	struct zpci_fib fib = {0};
	u8 status;

	fib.fmt = 1;
	fib.fmt1.noi = zdev->msi_nr_irqs;
	fib.fmt1.dibvo = zdev->msi_first_bit;

	return zpci_mod_fc(req, &fib, &status) ? -EIO : 0;
}