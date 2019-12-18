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
struct fw_xfer {int flag; scalar_t__ resp; int /*<<< orphan*/ * fc; TYPE_1__* q; } ;
struct TYPE_2__ {int /*<<< orphan*/  queued; int /*<<< orphan*/  q; } ;

/* Variables and functions */
 int FWXF_INIT ; 
 int FWXF_INQ ; 
 int FWXF_START ; 
 int /*<<< orphan*/  FW_GLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FW_GUNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE (int /*<<< orphan*/ *,struct fw_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_tl_free (int /*<<< orphan*/ *,struct fw_xfer*) ; 
 int /*<<< orphan*/  fw_xfer ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  printf (char*) ; 

void
fw_xfer_unload(struct fw_xfer *xfer)
{

	if (xfer == NULL)
		return;

	if (xfer->fc != NULL) {
		FW_GLOCK(xfer->fc);
		if (xfer->flag & FWXF_INQ) {
			STAILQ_REMOVE(&xfer->q->q, xfer, fw_xfer, link);
			xfer->flag &= ~FWXF_INQ;
	#if 0
			xfer->q->queued--;
	#endif
		}
		FW_GUNLOCK(xfer->fc);

		/*
		 * Ensure that any tlabel owner can't access this
		 * xfer after it's freed.
		 */
		fw_tl_free(xfer->fc, xfer);
#if 1
		if (xfer->flag & FWXF_START)
			/*
			 * This could happen if:
			 *  1. We call fwohci_arcv() before fwohci_txd().
			 *  2. firewire_watch() is called.
			 */
			printf("fw_xfer_free FWXF_START\n");
#endif
	}
	xfer->flag = FWXF_INIT;
	xfer->resp = 0;
}