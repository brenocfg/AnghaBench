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
struct sbp_dev {TYPE_1__* target; } ;
struct fw_xfer {scalar_t__ sc; } ;
struct TYPE_2__ {int /*<<< orphan*/  xferlist; int /*<<< orphan*/  sbp; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBP_LOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct fw_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_xfer_unload (struct fw_xfer*) ; 
 int /*<<< orphan*/  link ; 

__attribute__((used)) static __inline void
sbp_xfer_free(struct fw_xfer *xfer)
{
	struct sbp_dev *sdev;

	sdev = (struct sbp_dev *)xfer->sc;
	fw_xfer_unload(xfer);
	SBP_LOCK_ASSERT(sdev->target->sbp);
	STAILQ_INSERT_TAIL(&sdev->target->xferlist, xfer, link);
}