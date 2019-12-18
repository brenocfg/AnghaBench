#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {int sum; unsigned long aibv; unsigned long aisb; int aisbo; scalar_t__ aibvo; int /*<<< orphan*/  noi; int /*<<< orphan*/  isc; } ;
struct zpci_fib {TYPE_1__ fmt0; int /*<<< orphan*/  member_0; } ;
struct zpci_dev {int aisb; TYPE_3__* aibv; int /*<<< orphan*/  fh; } ;
struct TYPE_6__ {scalar_t__ vector; } ;
struct TYPE_5__ {scalar_t__ vector; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PCI_ISC ; 
 int /*<<< orphan*/  ZPCI_CREATE_REQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZPCI_MOD_FC_REG_INT ; 
 int /*<<< orphan*/  airq_iv_end (TYPE_3__*) ; 
 scalar_t__ zpci_mod_fc (int /*<<< orphan*/ ,struct zpci_fib*,int /*<<< orphan*/ *) ; 
 TYPE_2__* zpci_sbv ; 

__attribute__((used)) static int zpci_set_airq(struct zpci_dev *zdev)
{
	u64 req = ZPCI_CREATE_REQ(zdev->fh, 0, ZPCI_MOD_FC_REG_INT);
	struct zpci_fib fib = {0};
	u8 status;

	fib.fmt0.isc = PCI_ISC;
	fib.fmt0.sum = 1;	/* enable summary notifications */
	fib.fmt0.noi = airq_iv_end(zdev->aibv);
	fib.fmt0.aibv = (unsigned long) zdev->aibv->vector;
	fib.fmt0.aibvo = 0;	/* each zdev has its own interrupt vector */
	fib.fmt0.aisb = (unsigned long) zpci_sbv->vector + (zdev->aisb/64)*8;
	fib.fmt0.aisbo = zdev->aisb & 63;

	return zpci_mod_fc(req, &fib, &status) ? -EIO : 0;
}