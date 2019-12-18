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
struct fw_xfer {int /*<<< orphan*/  fc; scalar_t__ sc; } ;
struct fw_drv1 {int /*<<< orphan*/  rq; } ;
struct fw_bind {struct fw_drv1* sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_GLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_GUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct fw_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fw_hand(struct fw_xfer *xfer)
{
	struct fw_bind *fwb;
	struct fw_drv1 *d;

	fwb = (struct fw_bind *)xfer->sc;
	d = fwb->sc;
	FW_GLOCK(xfer->fc);
	STAILQ_INSERT_TAIL(&d->rq, xfer, link);
	FW_GUNLOCK(xfer->fc);
	wakeup(&d->rq);
}